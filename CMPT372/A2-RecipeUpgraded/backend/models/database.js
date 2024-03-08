const { Pool } = require("pg");
var pool = new Pool({
   user: "postgres",
   host: "db",
   password: "root",
});

//* ======================= HELPERS =======================
// PARAMETERS: ingredients (array of strings)
async function ingredientToId(ingredients) {
   // Convert each ingredient to its corresponding ID
   const ingredientIds = [];
   for (let ingredient of ingredients) {
      let res = await pool.query("SELECT iid FROM ingredients WHERE ingredient = $1", [ingredient]);
      let id;
      if (res.rows.length === 0) {
         // If the ingredient does not exist, add it to the ingredients table and retrieve its ID
         res = await pool.query("INSERT INTO ingredients (ingredient) VALUES ($1) RETURNING iid", [
            ingredient,
         ]);
         id = res.rows[0].iid;
      } else {
         // If the ingredient exists, retrieve its ID
         id = res.rows[0].iid;
      }
      ingredientIds.push(id);
   }
   return ingredientIds;
}

async function checkIfRecipeExists(id) {
   // Ensure recipe exists
   const existingRecipe = await getRecipeById(id);
   if (!existingRecipe) {
      throw new Error(`Recipe with ID ${id} does not exist`);
   }
}

async function init() {
   const createIngredientsTable =
      "CREATE TABLE IF NOT EXISTS ingredients (iid SERIAL PRIMARY KEY, ingredient VARCHAR(255))";

   const createRecipeTable =
      "CREATE TABLE IF NOT EXISTS recipes (rid SERIAL PRIMARY KEY, title VARCHAR(255), time_modified VARCHAR(30),ingredient_ids INT[],instructions TEXT)";

   await pool.query(createIngredientsTable);
   await pool.query(createRecipeTable);
}

//* ======================= ENDPOINTS =======================
async function getRecipes() {
   const res = await pool.query("SELECT * FROM recipes");
   const recipes = res.rows;

   // For each recipe, retrieve its ingredients and add them to the recipe
   for (let recipe of recipes) {
      const ingredientRes = await pool.query(
         "SELECT ingredient FROM ingredients WHERE iid = ANY($1)",
         [recipe.ingredient_ids]
      );
      recipe.ingredients = ingredientRes.rows.map((row) => row.ingredient);
   }

   return recipes;
}

// PARAMETERS: id (number)
async function getRecipeById(id) {
   const res = await pool.query("SELECT * FROM recipes WHERE rid = $1", [id]);
   const recipe = res.rows[0];

   // If the recipe exists, retrieve its ingredients
   if (recipe) {
      const ingredientRes = await pool.query(
         "SELECT ingredient FROM ingredients WHERE iid = ANY($1)",
         [recipe.ingredient_ids]
      );
      recipe.ingredients = ingredientRes.rows.map((row) => row.ingredient);
   }

   return recipe;
}

// PARAMETERS: recipe (object), ingredients (array of strings)
async function addRecipe(recipe, ingredients) {
   const ingredientIds = await ingredientToId(ingredients);

   // Add the recipe to the recipes table
   const insertRecipe = `
        INSERT INTO recipes (title, time_modified, ingredient_ids, instructions)
        VALUES ($1, $2, $3, $4)
    `;
   await pool.query(insertRecipe, [
      recipe.title,
      recipe.time_modified,
      ingredientIds,
      recipe.instructions,
   ]);
}

// PARAMETERS: id (number), recipe (object), ingredients (array of strings)
async function updateRecipe(id, recipe, ingredients) {
   await checkIfRecipeExists(id);
   const ingredientIds = await ingredientToId(ingredients);

   // Update existing recipe
   const updateRecipeQuery = `
        UPDATE recipes 
        SET title = $1, time_modified = $2, ingredient_ids = $3, instructions = $4
        WHERE rid = $5
    `;
   await pool.query(updateRecipeQuery, [
      recipe.title,
      recipe.time_modified,
      ingredientIds,
      recipe.instructions,
      id,
   ]);
}

// PARAMETERS: id (number)
async function deleteRecipe(id) {
   await checkIfRecipeExists(id);
   await pool.query("DELETE FROM recipes WHERE rid = $1", [id]);
}

module.exports = {
   init,
   getRecipes,
   getRecipeById,
   addRecipe,
   updateRecipe,
   deleteRecipe,
};
