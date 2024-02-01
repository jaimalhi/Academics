<script lang="ts">
	import '../../app.postcss';
	import { page } from '$app/stores';

	import { AppShell, AppBar } from '@skeletonlabs/skeleton';
	import { initializeStores } from '@skeletonlabs/skeleton';
	import { Toast, getToastStore } from '@skeletonlabs/skeleton';
	import type { ToastSettings, ToastStore } from '@skeletonlabs/skeleton';
	import { goto } from '$app/navigation';

	initializeStores();

	// reactive variables
	$: currentRoute = $page.route.id;
	$: addRecipeBtn = currentRoute === '/recipes/add' ? true : false;
</script>

<svelte:head>
	<title>Recipe App</title>
	<meta name="description" content="Simple recipe app created with sveltekit & skeleton" />
</svelte:head>

<Toast position="tr" />

<AppShell>
	<svelte:fragment slot="header">
		<AppBar gridColumns="grid-cols-3" slotDefault="place-self-center" slotTrail="place-content-end">
			<svelte:fragment slot="lead">
				<a href="/recipes" class="h2 hover:text-primary-500 font-medium">
					<i class="fa-solid fa-house text-4xl"></i>
				</a>
			</svelte:fragment>
			<h1 class="text-4xl">Recipe App</h1>
			<svelte:fragment slot="trail">
				<button
					on:click={() => {
						goto('/recipes/add');
					}}
					disabled={addRecipeBtn}
					class="btn variant-filled hover:bg-primary-500 hover:text-white">Add Recipe</button
				>
			</svelte:fragment>
		</AppBar>
	</svelte:fragment>
	<!-- Router Slot -->
	<div class="container p-10 mx-auto">
		<slot />
	</div>
	<!-- ---- / ---- -->
	<svelte:fragment slot="footer">
		<AppBar gridColumns="grid-cols-1" slotDefault="place-self-center">
			<a class="anchor" href="https://kit.svelte.dev/">Sveltekit</a>
			+
			<a class="anchor" href="https://www.skeleton.dev/">Skeleton</a>
		</AppBar>
	</svelte:fragment>
</AppShell>
