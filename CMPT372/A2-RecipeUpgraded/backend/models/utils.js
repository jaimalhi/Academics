const { Pool } = require("pg");
var pool = new Pool({
   user: "postgres",
   host: "db",
   password: "root",
});

// PARAMETERS: ingredients (array of strings)
async function ingredientToId(ingredients) {
   // Convert each ingredient to its corresponding ID
   let ingredientIds = [];
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

module.exports = { ingredientToId };
