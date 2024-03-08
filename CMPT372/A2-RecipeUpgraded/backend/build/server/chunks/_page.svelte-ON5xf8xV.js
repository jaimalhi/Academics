import { c as create_ssr_component, e as escape, i as each } from './ssr-V-Hd1H2_.js';

function formatDate(dateString) {
  const date = new Date(dateString);
  const day = String(date.getDate()).padStart(2, "0");
  const month = String(date.getMonth() + 1).padStart(2, "0");
  const year = date.getFullYear();
  const hours = String(date.getHours()).padStart(2, "0");
  const minutes = String(date.getMinutes()).padStart(2, "0");
  const seconds = String(date.getSeconds()).padStart(2, "0");
  return `${day}-${month}-${year} @ ${hours}:${minutes}:${seconds}`;
}
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let { data } = $$props;
  if ($$props.data === void 0 && $$bindings.data && data !== void 0)
    $$bindings.data(data);
  return `<div class="container mx-auto flex flex-col flex-grow min-h-80 border-2 bg-surface-700 rounded-xl p-4">${data.recipe ? `<header class="header"><h1 class="text-4xl mb-3">${escape(data.recipe.title)}</h1> <span class="opacity-50">${escape(formatDate(new Date(data.recipe.time_modified)))}</span></header> <hr class="!border-t-4 !border-primary-500 opacity-70"> <section class="flex flex-col my-3"><span class="text-xl underline" data-svelte-h="svelte-1dlhxw7">Ingredients</span> <ol>${each(data.recipe.ingredients, (ingredient, index) => {
    return `<li class="opacity-80"><span>${escape(index + 1)}.</span> <span>${escape(ingredient)}</span> </li>`;
  })}</ol></section> <hr class="!border-t-2 !border-primary-500 opacity-50"> <section class="flex flex-col my-2"><span class="text-xl underline" data-svelte-h="svelte-fjb4ia">Instructions</span> <span class="first-letter:uppercase">${escape(data.recipe.instructions)}</span></section>` : `<h1 class="text-5xl py-5" data-svelte-h="svelte-qw1cku">Recipe not found...</h1> <a class="anchor" href="/recipes" data-svelte-h="svelte-13mb37v">Return Home</a>`}</div>`;
});

export { Page as default };
//# sourceMappingURL=_page.svelte-ON5xf8xV.js.map
