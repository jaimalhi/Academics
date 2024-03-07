import { recipeStore, type Recipe } from '$lib/stores';
import { get } from 'svelte/store';
import type { PageLoad } from './$types';

export const load: PageLoad = ({ params }) => {
	// get data from local storage
	const currentRecipe: Recipe | undefined = get(recipeStore).find((r) => r.id === params.recipe_id);

	// handle the case when the recipe is not found
	if (!currentRecipe) {
		return {
			recipe: null
		};
	}

	return {
		recipe: {
			name: currentRecipe.name,
			ingredients: currentRecipe.ingredients,
			instructions: currentRecipe.instructions
		}
	};
};
