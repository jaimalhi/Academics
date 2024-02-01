import { redirect } from '@sveltejs/kit';

// redirect all requests to root / to /recipes
export function load() {
	redirect(301, '/recipes'); // needs `throw` in v1
}
