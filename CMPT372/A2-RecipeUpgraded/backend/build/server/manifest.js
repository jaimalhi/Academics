const manifest = (() => {
function __memo(fn) {
	let value;
	return () => value ??= (value = fn());
}

return {
	appDir: "_app",
	appPath: "_app",
	assets: new Set(["favicon.png"]),
	mimeTypes: {".png":"image/png"},
	_: {
		client: {"start":"_app/immutable/entry/start.laRiE7RC.js","app":"_app/immutable/entry/app.i7ATzsz8.js","imports":["_app/immutable/entry/start.laRiE7RC.js","_app/immutable/chunks/entry.Gzexlnjv.js","_app/immutable/chunks/scheduler.OWaxIzIJ.js","_app/immutable/chunks/control.pJ1mnnAb.js","_app/immutable/entry/app.i7ATzsz8.js","_app/immutable/chunks/scheduler.OWaxIzIJ.js","_app/immutable/chunks/index.3LzlWLC8.js"],"stylesheets":[],"fonts":[],"uses_env_dynamic_public":false},
		nodes: [
			__memo(() => import('./chunks/0-EbCMtCue.js')),
			__memo(() => import('./chunks/1-8dLPTAjr.js')),
			__memo(() => import('./chunks/2-ENPPcIP7.js')),
			__memo(() => import('./chunks/3-rVaOkHyK.js')),
			__memo(() => import('./chunks/4-lwDqQEXY.js')),
			__memo(() => import('./chunks/5-Pk7BcBaL.js')),
			__memo(() => import('./chunks/6-EAt4biEn.js')),
			__memo(() => import('./chunks/7-tfG1XrdY.js'))
		],
		routes: [
			{
				id: "/",
				pattern: /^\/$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 3 },
				endpoint: null
			},
			{
				id: "/recipes",
				pattern: /^\/recipes\/?$/,
				params: [],
				page: { layouts: [0,2,], errors: [1,,], leaf: 4 },
				endpoint: null
			},
			{
				id: "/recipes/add",
				pattern: /^\/recipes\/add\/?$/,
				params: [],
				page: { layouts: [0,2,], errors: [1,,], leaf: 5 },
				endpoint: null
			},
			{
				id: "/recipes/[recipe_id]",
				pattern: /^\/recipes\/([^/]+?)\/?$/,
				params: [{"name":"recipe_id","optional":false,"rest":false,"chained":false}],
				page: { layouts: [0,2,], errors: [1,,], leaf: 6 },
				endpoint: null
			},
			{
				id: "/recipes/[recipe_id]/update",
				pattern: /^\/recipes\/([^/]+?)\/update\/?$/,
				params: [{"name":"recipe_id","optional":false,"rest":false,"chained":false}],
				page: { layouts: [0,2,], errors: [1,,], leaf: 7 },
				endpoint: null
			}
		],
		matchers: async () => {
			
			return {  };
		},
		server_assets: {}
	}
}
})();

const prerendered = new Set([]);

const base = "";

export { base, manifest, prerendered };
//# sourceMappingURL=manifest.js.map
