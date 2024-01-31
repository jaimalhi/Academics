// main.ts
import { PigManager } from "./pig-manager";

const pigManager = new PigManager();

// Function to create the main page with a list of pigs
function createMainPage() {
   const app = document.getElementById("app");
   if (!app) return;

   // add pig functionality
   pigManager.addPig();
   pigManager.displayPigs();
}

// Initialize the main page
createMainPage();

// TODO
// - add error checking for inputs
