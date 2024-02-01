<script lang="ts">
	import { goto } from '$app/navigation';
	import { recipeStore } from '$lib/stores';
	import { formatDate } from '$lib/utils/dateFormatter';

	import { getModalStore, getToastStore, type ModalSettings } from '@skeletonlabs/skeleton';

	const modalStore = getModalStore();
	const toastStore = getToastStore();

	function goToRecipe(recipeId: string) {
		// goto(`/recipes/${recipeId}`);
		console.log(recipeId);
	}

	function deleteRecipe(recipeId: string) {
		const confirmDelete: ModalSettings = {
			type: 'confirm',
			title: 'Please Confirm',
			body: 'Are you sure you wish to delete the recipe?',
			response(r: boolean) {
				if (r) {
					recipeStore.update((recipes) => {
						return recipes.filter((r) => r.id !== recipeId);
					});
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
</script>

<div class="flex flex-wrap gap-8">
	{#each $recipeStore as recipe}
		<section class="card card-hover overflow-hidden w-60 flex-grow">
			<header class="card-header">
				<h3 class="h3 underline underline-offset-2">{recipe.name}</h3>
				<span class="opacity-50">
					{formatDate(recipe.createdAt)}
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
						deleteRecipe(recipe.id);
					}}
					type="button"
					class="btn w-1/2 mx-2 variant-filled hover:bg-error-500 hover:text-white"
					>Delete Recipe</button
				>
				<button
					on:click={() => {
						goToRecipe(recipe.id);
					}}
					type="button"
					class="btn w-1/2 mx-2 variant-filled hover:bg-primary-500 hover:text-white"
					>View Recipe</button
				>
			</footer>
		</section>
	{/each}
</div>
