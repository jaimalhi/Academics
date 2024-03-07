// npm modules
const express = require("express");
const serveIndex = require("serve-index");
let app = express();
// node modules
let path = require("path");
let fs = require("fs");
let http = require("http");

const port = 8080;

// parsing body
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// static files
app.use("/", express.static(path.join(__dirname, "./static"), { index: ["home.html"] }));

// Get all recipes
app.get("/api/recipes", async (req, res) => {
   // TODO
   res.json(r);
});

// Get a recipe by id
app.get("/api/recipes/:id", async (req, res) => {
   // TODO
   let id = req.params.id;
   res.json(r);
});

//

async function InitDB() {
   await db.helpers.init();
   const p = await db.helpers.getPeople();
   console.log(p);
   people = p;
}

InitDB()
   .then(() => {
      app.listen(port, () => {
         console.log(`server is running on port ${port}`);
      });
   })
   .catch((err) => {
      console.log(err);
   });
