// npm modules
const express = require("express");
let app = express();
// node modules
let path = require("path");
let db = require("./models/database");

const port = 8080;

// parsing body
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// static files
app.use("/", express.static(path.join(__dirname, "./static"), { index: ["home.html"] }));

// Get all recipes
app.get("/api/recipes", async (req, res) => {
   db.getRecipes()
      .then((recipe) => {
         res.json(recipe);
      })
      .catch((err) => {
         console.log(err);
         res.status(500).send("Error");
      });
});

// Get a recipe by id
app.get("/api/recipes/:id", async (req, res) => {
   let id = req.params.id;
   db.getRecipeById(id)
      .then((recipe) => {
         res.json(recipe);
      })
      .catch((err) => {
         console.log(err);
         res.status(500).send("Error");
      });
});

app.post("/api/add", async (req, res) => {
   let recipe = {
      title: req.body.title,
      time_modified: req.body.time_modified,
      instructions: req.body.instructions,
   };
   let ingredients = req.body.ingredients;
   db.addRecipe(recipe, ingredients)
      .then(() => {
         res.status(201).send("Success adding recipe");
      })
      .catch((err) => {
         console.log(err);
         res.status(500).send("Error adding recipe");
      });
});

app.delete("/api/delete/:id", async (req, res) => {
   let id = req.params.id;
   db.deleteRecipe(id)
      .then(() => {
         res.status(200).send("Success deleting recipe");
      })
      .catch((err) => {
         console.log(err);
         res.status(500).send("Error deleting recipe");
      });
});

// TODO: route to update a recipe
app.put("/api/update/:id", async (req, res) => {
   let id = req.params.id;
   let recipe = {
      title: req.body.title,
      time_modified: req.body.time_modified,
      instructions: req.body.instructions,
   };
   let ingredients = req.body.ingredients;
   db.updateRecipe(id, recipe, ingredients)
      .then(() => {
         res.status(200).send("Success updating recipe");
      })
      .catch((err) => {
         console.log(err);
         res.status(500).send("Error updating recipe");
      });
});

// Initalize the database
async function InitDB() {
   await db.init();
   const recipes = await db.getRecipes();
   console.log("========== Recipes ==========");
   console.log(recipes);
   console.log("=============================");
}

InitDB()
   .then(() => {
      app.listen(port, "0.0.0.0", () => {
         console.log(`App listening at http://localhost:${port}`);
         console.log(`App listening at http://0.0.0.0:${port}`);
      });
   })
   .catch((err) => {
      console.log(err);
   });
