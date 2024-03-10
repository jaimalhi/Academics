<script lang="ts">
	import type { PageData } from './$types';
	// get data from locale storage using +page.ts via load function
	export let data: PageData;

	import { InputChip, getToastStore, type ToastSettings } from '@skeletonlabs/skeleton';
	import { goto } from '$app/navigation';

	let title: string;
	let ingredients: string[];
	let instructions: string;
	let rid: number;
	// ensure recipe is not undefined
	if (data.recipe) {
		title = data.recipe.title;
		ingredients = data.recipe.ingredients;
		instructions = data.recipe.instructions;
		rid = data.recipe.rid;
	}

	// control disabled state of buttons
	$: createRecipeBtn = title && ingredients.length > 0 && instructions ? true : false;

	const toastStore = getToastStore();
	const t: ToastSettings = {
		message: 'Recipe added successfully!',
		background: 'variant-filled-success'
	};

	async function updateRecipe() {
		const recipe = {
			title,
			instructions,
			ingredients,
			time_modified: new Date()
		};

		try {
			await fetch(`http://localhost:3000/api/update/${rid}`, {
				method: 'PUT',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify(recipe)
			});
		} catch (error) {
			console.error('Error:', error);
		}
		// reset form after adding recipe
		title = '';
		ingredients = [];
		instructions = '';
		toastStore.trigger(t);
		goto('/recipes');
	}

	function resetRecipe() {
		title = '';
		ingredients = [];
		instructions = '';
	}
</script>

<div
	class="container mx-auto flex flex-col flex-grow min-h-80 border-2 bg-surface-700 rounded-xl p-4"
>
	{#if data.recipe}
		<div class="flex flex-col gap-4 bg-surface-700 p-5 rounded-lg">
			<h1 class="text-xl">Update Recipe</h1>
			<hr class="!border-t-4" />
			<form method="POST">
				<!-- title -->
				<label class="label mb-3" for="recipe-title">
					<span>Title</span>
					<input
						bind:value={title}
						class="input rounded-lg"
						id="recipe-title"
						type="text"
						placeholder="Recipe Title..."
						name="title"
					/>
				</label>
				<!-- Ingredients -->
				<label class="label mb-3" for="ingredient-list">
					<span>Ingredients</span>
					<InputChip
						bind:value={ingredients}
						name="chips"
						id="ingredient-list"
						placeholder="Enter ingredient one at a time..."
					/>
				</label>
				<!-- Instructions -->
				<label class="label mb-3" for="instructions">
					<span>Instructions</span>
					<textarea
						bind:value={instructions}
						class="textarea rounded-lg"
						id="instructions"
						name="instructions"
						rows="4"
						placeholder="Step-by-Step Recipe instructions..."
					/>
				</label>
				<section class="flex justify-around">
					<button
						on:click={resetRecipe}
						type="button"
						class="btn variant-filled hover:bg-error-500 hover:text-white"
					>
						Reset Recipe
					</button>
					<button
						on:click={updateRecipe}
						disabled={!createRecipeBtn}
						type="button"
						class="btn variant-filled hover:bg-primary-500 hover:text-white">Update Recipe</button
					>
				</section>
			</form>
		</div>
	{:else}
		<h1 class="text-5xl py-5">Recipe not found...</h1>
		<a class="anchor" href="/recipes">Return Home</a>
	{/if}
</div>
