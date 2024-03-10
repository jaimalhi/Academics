const load = async ({ params }) => {
  const currentRecipe = await loadRecipe(params.recipe_id);
  if (!currentRecipe) {
    return {
      recipe: null
    };
  }
  return {
    recipe: {
      rid: currentRecipe.rid,
      title: currentRecipe.title,
      ingredients: currentRecipe.ingredients,
      instructions: currentRecipe.instructions
    }
  };
};
async function loadRecipe(recipeId) {
  try {
    const res = await fetch(`http://localhost:3000/api/recipes/${recipeId}`, {
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

const index = 7;
let component_cache;
const component = async () => component_cache ??= (await import('./_page.svelte-HeWzWlbt.js')).default;
const universal_id = "src/routes/recipes/[recipe_id]/update/+page.ts";
const imports = ["_app/immutable/nodes/7.n9rZsUS8.js","_app/immutable/chunks/scheduler.OWaxIzIJ.js","_app/immutable/chunks/index.3LzlWLC8.js","_app/immutable/chunks/ProgressBar.svelte_svelte_type_style_lang.Ov6B9o8A.js","_app/immutable/chunks/entry.Gzexlnjv.js","_app/immutable/chunks/control.pJ1mnnAb.js","_app/immutable/chunks/InputChip.50wspIVn.js","_app/immutable/chunks/index.XdmiYZQk.js","_app/immutable/chunks/each.smOdYV4G.js"];
const stylesheets = ["_app/immutable/assets/ProgressBar.oq5aOWfL.css"];
const fonts = [];

export { component, fonts, imports, index, stylesheets, _page_ts as universal, universal_id };
//# sourceMappingURL=7-tfG1XrdY.js.map
