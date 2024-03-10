<script lang="ts">
	import { InputChip, getToastStore, type ToastSettings } from '@skeletonlabs/skeleton';
	import { goto } from '$app/navigation';

	// form state
	let title: string;
	let ingredients: string[] = ['water'];
	let instructions: string;

	// control disabled state of buttons
	$: createRecipeBtn = title && ingredients.length > 0 && instructions ? true : false;

	const toastStore = getToastStore();
	const t: ToastSettings = {
		message: 'Recipe added successfully!',
		background: 'variant-filled-success'
	};

	async function createRecipe() {
		const recipe = {
			title,
			instructions,
			ingredients,
			time_modified: new Date()
		};

		try {
			await fetch('http://localhost:3000/api/add', {
				method: 'POST',
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

<div class="flex flex-col gap-4 bg-surface-700 p-5 rounded-lg">
	<h1 class="text-xl">New Recipe</h1>
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
				on:click={createRecipe}
				disabled={!createRecipeBtn}
				type="button"
				class="btn variant-filled hover:bg-primary-500 hover:text-white">Create Recipe</button
			>
		</section>
	</form>
</div>
