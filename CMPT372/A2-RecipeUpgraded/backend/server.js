// Using CommonJS syntax
// const express = require("express");
// const { handler } = require("./build/index.js");
// let path = require("path");
// let cors = require("cors");
// let db = require("./models/database");

// Importing modules using ES6 syntax
import express from "express";
import { handler } from "./build/handler.js";
import path from "path";
import cors from "cors";
import * as db from "./models/database.js";

const app = express();
const port = 8080;

app.use(express.json()); // parsing body
app.use(express.urlencoded({ extended: true }));
app.use(cors());

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

// Add a recipe
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

// Delete a recipe by id
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

// Update a recipe by id
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

// Use the SvelteKit handler to handle all other requests
app.use(handler);

// Initialize the database and start the server
async function initDBAndStartServer() {
   try {
      await db.init();
      const recipes = await db.getRecipes();

      app.listen(port, "0.0.0.0", () => {
         console.log("================== Starting Server ==================");
         console.log(`App listening at http://localhost:${port} with ${recipes.length} recipes`);
         console.log("=====================================================");
      });
   } catch (err) {
      console.error("Failed to initialize the database or start the server:", err);
   }
}

initDBAndStartServer();
