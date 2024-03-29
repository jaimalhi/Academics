import { localStorageStore } from '@skeletonlabs/skeleton';
import type { Writable } from 'svelte/store';

export type Recipe = {
	id: string;
	name: string;
	ingredients: string[];
	instructions: string;
	createdAt: Date;
};

// Create a writable store that will be saved to local storage
export const recipeStore: Writable<Recipe[]> = localStorageStore<Recipe[]>('recipes', []);
