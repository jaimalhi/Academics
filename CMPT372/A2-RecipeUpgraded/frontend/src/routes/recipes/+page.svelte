<script lang="ts">
	import { goto } from '$app/navigation';
	import { formatDate } from '$lib/utils/dateFormatter';
	import { formatRecipe } from '$lib/utils/recipeFormatter';
	import type { Recipe } from '$lib/models/recipes';

	import { getModalStore, getToastStore, type ModalSettings } from '@skeletonlabs/skeleton';
	import { onMount } from 'svelte';

	const modalStore = getModalStore();
	const toastStore = getToastStore();

	// array to hold recipes
	let recipes: Recipe[];
	let isLoading = true;

	async function loadRecipes() {
		try {
			const res = await fetch('http://localhost:3000/api/recipes', {
				method: 'GET',
				headers: {
					'Content-Type': 'application/json'
				}
			});
			const data = await res.json();
			recipes = data.map(formatRecipe);
			// console.log(recipes);
		} catch (error) {
			console.log('===== ERROR LOADING RECIPES =====');
			console.log(error);
		}
	}

	async function deleteRecipeById(recipeId: number) {
		try {
			// delete recipe by id from server
			await fetch(`http://localhost:3000/api/delete/${recipeId}`, {
				method: 'DELETE',
				headers: {
					'Content-Type': 'application/json'
				}
			});
			// return recipes without the deleted recipe
			recipes = recipes.filter((recipe) => recipe.rid !== recipeId);
		} catch (error) {
			console.log('===== ERROR DELETING RECIPE =====');
			console.log(error);
		}
	}

	async function deleteRecipeOnClick(recipeId: number) {
		const confirmDelete: ModalSettings = {
			type: 'confirm',
			title: 'Please Confirm',
			body: 'Are you sure you wish to delete the recipe?',
			async response(r: boolean) {
				if (r) {
					await deleteRecipeById(recipeId);
					// show toast
					toastStore.trigger({
						message: 'Recipe delete successfully!',
						background: 'variant-filled-success'
					});
				} else {
					toastStore.trigger({
						message: 'Recipe did not delete',
						background: 'variant-filled-error'
					});
				}
			}
		};
		modalStore.trigger(confirmDelete);
	}

	function goToRecipeWithRid(recipeId: number) {
		goto(`/recipes/${recipeId}`);
	}

	function updateRecipeWithRid(recipeId: number) {
		goto(`/recipes/${recipeId}/update`);
	}

	// load recipes on mount/initial render
	onMount(async () => {
		await loadRecipes();
		isLoading = false;
	});
</script>

{#if isLoading}
	<div class="p-4 space-y-4" class:animate-pulse={true}>
		<div class="placeholder" />
		<div class="grid grid-cols-4 gap-4">
			<div class="placeholder" />
			<div class="placeholder" />
			<div class="placeholder" />
			<div class="placeholder" />
		</div>
		<div class="placeholder" />
		<div class="grid grid-cols-4 gap-4">
			<div class="placeholder" />
			<div class="placeholder" />
			<div class="placeholder" />
			<div class="placeholder" />
		</div>
		<div class="placeholder" />
	</div>
{:else}
	<div class="flex flex-wrap gap-8">
		{#each recipes as recipe}
			<section class="card card-hover overflow-hidden w-auto flex-grow">
				<header class="card-header">
					<h3 class="h3 underline underline-offset-2">{recipe.title}</h3>
					<span class="opacity-50">
						{formatDate(new Date(recipe.time_modified))}
					</span>
				</header>
				<article class="p-4 h-40">
					<!-- Ensure max 4 ingredients visible -->
					<ol class="list">
						{#each recipe.ingredients.slice(0, 5) as ingredient, index (ingredient)}
							{#if index < 4}
								<li>
									<span>{index + 1}.</span>
									<span class="flex-auto">{ingredient}</span>
								</li>
							{:else}
								<li>
									<span>{index + 1}.</span>
									<span class="flex-auto">...</span>
								</li>
							{/if}
						{/each}
					</ol>
				</article>
				<hr class="opacity-50" />
				<footer class="card-footer p-4 flex justify-center">
					<button
						on:click={() => {
							deleteRecipeOnClick(recipe.rid);
						}}
						type="button"
						class="btn w-1/2 mx-2 variant-filled hover:bg-error-500 hover:text-white"
						>Delete Recipe</button
					>
					<button
						on:click={() => {
							updateRecipeWithRid(recipe.rid);
						}}
						type="button"
						class="btn w-1/2 mx-2 variant-filled hover:bg-secondary-500 hover:text-white"
						>Update Recipe</button
					>
					<button
						on:click={() => {
							goToRecipeWithRid(recipe.rid);
						}}
						type="button"
						class="btn w-1/2 mx-2 variant-filled hover:bg-primary-500 hover:text-white"
						>View Recipe</button
					>
				</footer>
			</section>
		{/each}
	</div>
{/if}
