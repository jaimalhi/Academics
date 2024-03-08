<script lang="ts">
	import { formatDate } from '$lib/utils/dateFormatter';
	import type { PageData } from './$types';
	// get data from locale storage using +page.ts via load function
	export let data: PageData;
</script>

<div
	class="container mx-auto flex flex-col flex-grow min-h-80 border-2 bg-surface-700 rounded-xl p-4"
>
	{#if data.recipe}
		<header class="header">
			<h1 class="text-4xl mb-3">
				{data.recipe.title}
			</h1>
			<span class="opacity-50">
				{formatDate(new Date(data.recipe.time_modified))}
			</span>
		</header>
		<hr class="!border-t-4 !border-primary-500 opacity-70" />
		<section class="flex flex-col my-3">
			<span class="text-xl underline">Ingredients</span>
			<ol>
				{#each data.recipe.ingredients as ingredient, index (ingredient)}
					<li class="opacity-80">
						<span>{index + 1}.</span>
						<span>{ingredient}</span>
					</li>
				{/each}
			</ol>
		</section>
		<hr class="!border-t-2 !border-primary-500 opacity-50" />
		<section class="flex flex-col my-2">
			<span class="text-xl underline">Instructions</span>
			<span class="first-letter:uppercase">
				{data.recipe.instructions}
			</span>
		</section>
	{:else}
		<h1 class="text-5xl py-5">Recipe not found...</h1>
		<a class="anchor" href="/recipes">Return Home</a>
	{/if}
</div>
