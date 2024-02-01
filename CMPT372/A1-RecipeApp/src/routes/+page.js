import { redirect } from '@sveltejs/kit';

// redirect all requests to root / to /recipes
export function load() {
	redirect(302, '/recipes'); // needs `throw` in v1
}
