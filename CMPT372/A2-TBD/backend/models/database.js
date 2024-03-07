const { Pool } = require("pg");
var pool = new Pool({
   user: "postgres",
   host: "db",
   password: "root",
});

async function getRecipes() {
   const res = await pool.query("SELECT * FROM people");
   return res.rows;
}

async function getRecipeById(id) {}

async function addRecipe(recipe, ingredients) {}

async function init() {
   const query =
      "CREATE TABLE IF NOT EXISTS recipes(rid SERIAL PRIMARY KEY, name VARCHAR(50), age INT, instructor BOOLEAN)";
   const res = await pool.query(query);
}

module.exports = { init };
