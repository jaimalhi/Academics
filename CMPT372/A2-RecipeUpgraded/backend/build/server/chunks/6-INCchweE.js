const load = async ({ params }) => {
  const currentRecipe = await loadRecipe(params.recipe_id);
  if (!currentRecipe) {
    return {
      recipe: null
    };
  }
  return {
    recipe: {
      title: currentRecipe.title,
      ingredients: currentRecipe.ingredients,
      instructions: currentRecipe.instructions,
      time_modified: currentRecipe.time_modified
    }
  };
};
async function loadRecipe(recipeId) {
  try {
    const res = await fetch(`http://localhost:8080/api/recipes/${recipeId}`, {
      method: "GET",
      headers: {
        "Content-Type": "application/json"
      }
    });
    const recipe = await res.json();
    return recipe;
  } catch (error) {
    console.log("===== ERROR LOADING RECIPE =====");
    console.log(error);
  }
}

var _page_ts = /*#__PURE__*/Object.freeze({
  __proto__: null,
  load: load
});

const index = 6;
let component_cache;
const component = async () => component_cache ??= (await import('./_page.svelte-ON5xf8xV.js')).default;
const universal_id = "src/routes/recipes/[recipe_id]/+page.ts";
const imports = ["_app/immutable/nodes/6.fRCvIHHd.js","_app/immutable/chunks/scheduler.OWaxIzIJ.js","_app/immutable/chunks/each.smOdYV4G.js","_app/immutable/chunks/index.3LzlWLC8.js","_app/immutable/chunks/dateFormatter.JrucCzqQ.js"];
const stylesheets = [];
const fonts = [];

export { component, fonts, imports, index, stylesheets, _page_ts as universal, universal_id };
//# sourceMappingURL=6-INCchweE.js.map
