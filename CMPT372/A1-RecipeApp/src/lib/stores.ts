import { localStorageStore } from '@skeletonlabs/skeleton';
import type { Writable } from 'svelte/store';

type Recipe = {
	id: number;
	name: string;
	ingredients: string[];
	insturctions: string[];
};

// Create a writable store that will be saved to local storage
export const recipeStore: Writable<Recipe[]> = localStorageStore<Recipe[]>('recipes', []);
