<script lang="ts">
	import { AppShell, AppBar, Avatar } from '@skeletonlabs/skeleton';
	import '../app.postcss';
</script>

<AppShell>
	<svelte:fragment slot="header">
		<AppBar>
			<svelte:fragment slot="lead">Recipe App</svelte:fragment>
			<svelte:fragment slot="trail"
				><Avatar initials="JM" background="bg-primary-500" width="w-12" /></svelte:fragment
			>
		</AppBar>
	</svelte:fragment>
	<!-- Router Slot -->
	<slot />
	<!-- ---- / ---- -->
	<svelte:fragment slot="pageFooter">Page Footer</svelte:fragment>
</AppShell>
