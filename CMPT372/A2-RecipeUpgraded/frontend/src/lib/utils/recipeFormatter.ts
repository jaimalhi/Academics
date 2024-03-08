import type { Recipe } from '$lib/models/recipes';

interface RecipeData {
	rid: number;
	title: string;
	time_modified: string;
	ingredient_ids: number[];
	instructions: string;
	ingredients: string[];
}

export function formatRecipe(recipeData: RecipeData) {
	const recipe: Recipe = {
		rid: recipeData.rid,
		title: recipeData.title,
		time_modified: recipeData.time_modified,
		instructions: recipeData.instructions,
		ingredients: recipeData.ingredients
	};

	return recipe;
}
