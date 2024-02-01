<script lang="ts">
	import { AppShell, AppBar } from '@skeletonlabs/skeleton';
	import '../../app.postcss';
	import { page } from '$app/stores';

	const rootRoute = $page.route.id; // new root -> /recipes
</script>

<svelte:head>
	<title>Sveltekit Recipe App</title>
	<meta name="description" content="Simple recipe app created with sveltekit & skeleton" />
</svelte:head>

<AppShell>
	<svelte:fragment slot="header">
		<AppBar gridColumns="grid-cols-3" slotDefault="place-self-center" slotTrail="place-content-end">
			<svelte:fragment slot="lead">
				<a href={rootRoute} class="h2 hover:text-primary-500 font-medium">
					<i class="fa-solid fa-house text-4xl"></i>
				</a>
			</svelte:fragment>
			<h1 class="text-4xl">Recipe App</h1>
			<svelte:fragment slot="trail">
				<a href="{rootRoute}/add" class="btn variant-filled hover:bg-primary-500 hover:text-white"
					>Add Recipe</a
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
