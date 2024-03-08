import { c as create_ssr_component, b as add_attribute, v as validate_component, e as escape } from './ssr-V-Hd1H2_.js';
import { g as getToastStore } from './ProgressBar.svelte_svelte_type_style_lang--QH1TJfj.js';
import { I as InputChip } from './InputChip-szkgPZLc.js';
import './exports-oiHf4OuW.js';
import './index2-Jzlktigj.js';

const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let createRecipeBtn;
  let { data } = $$props;
  let title;
  let ingredients;
  let instructions;
  if (data.recipe) {
    title = data.recipe.title;
    ingredients = data.recipe.ingredients;
    instructions = data.recipe.instructions;
    data.recipe.rid;
  }
  getToastStore();
  if ($$props.data === void 0 && $$bindings.data && data !== void 0)
    $$bindings.data(data);
  let $$settled;
  let $$rendered;
  let previous_head = $$result.head;
  do {
    $$settled = true;
    $$result.head = previous_head;
    createRecipeBtn = title && ingredients.length > 0 && instructions ? true : false;
    $$rendered = `<div class="container mx-auto flex flex-col flex-grow min-h-80 border-2 bg-surface-700 rounded-xl p-4">${data.recipe ? `<div class="flex flex-col gap-4 bg-surface-700 p-5 rounded-lg"><h1 class="text-xl" data-svelte-h="svelte-ia3zp8">Update Recipe</h1> <hr class="!border-t-4"> <form method="POST"> <label class="label mb-3" for="recipe-title"><span data-svelte-h="svelte-7ccxmo">Title</span> <input class="input rounded-lg" id="recipe-title" type="text" placeholder="Recipe Title..." name="title"${add_attribute("value", title, 0)}></label>  <label class="label mb-3" for="ingredient-list"><span data-svelte-h="svelte-qy8ztm">Ingredients</span> ${validate_component(InputChip, "InputChip").$$render(
      $$result,
      {
        name: "chips",
        id: "ingredient-list",
        placeholder: "Enter ingredient one at a time...",
        value: ingredients
      },
      {
        value: ($$value) => {
          ingredients = $$value;
          $$settled = false;
        }
      },
      {}
    )}</label>  <label class="label mb-3" for="instructions"><span data-svelte-h="svelte-l62uan">Instructions</span> <textarea class="textarea rounded-lg" id="instructions" name="instructions" rows="4" placeholder="Step-by-Step Recipe instructions...">${escape(instructions || "")}</textarea></label> <section class="flex justify-around"><button type="button" class="btn variant-filled hover:bg-error-500 hover:text-white" data-svelte-h="svelte-hgq1d7">Reset Recipe</button> <button ${!createRecipeBtn ? "disabled" : ""} type="button" class="btn variant-filled hover:bg-primary-500 hover:text-white">Update Recipe</button></section></form></div>` : `<h1 class="text-5xl py-5" data-svelte-h="svelte-qw1cku">Recipe not found...</h1> <a class="anchor" href="/recipes" data-svelte-h="svelte-13mb37v">Return Home</a>`}</div>`;
  } while (!$$settled);
  return $$rendered;
});

export { Page as default };
//# sourceMappingURL=_page.svelte-HeWzWlbt.js.map
