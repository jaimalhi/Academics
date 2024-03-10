import type { PageLoad } from './$types';
import type { Recipe } from '$lib/models/recipes';

export const load: PageLoad = async ({ params }) => {
	// get recipe from server
	const currentRecipe: Recipe = await loadRecipe(params.recipe_id);

	// handle the case when the recipe is not found
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

async function loadRecipe(recipeId: string) {
	try {
		const res = await fetch(`http://localhost:3000/api/recipes/${recipeId}`, {
			method: 'GET',
			headers: {
				'Content-Type': 'application/json'
			}
		});
		const recipe = await res.json();
		// console.log(recipe);
		return recipe;
	} catch (error) {
		console.log('===== ERROR LOADING RECIPE =====');
		console.log(error);
	}
}
