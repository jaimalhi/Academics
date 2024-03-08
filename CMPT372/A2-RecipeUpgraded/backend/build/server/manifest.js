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
		client: {"start":"_app/immutable/entry/start.q--MdpTG.js","app":"_app/immutable/entry/app.DLOf_woB.js","imports":["_app/immutable/entry/start.q--MdpTG.js","_app/immutable/chunks/entry.1-0VwD_A.js","_app/immutable/chunks/scheduler.OWaxIzIJ.js","_app/immutable/chunks/control.pJ1mnnAb.js","_app/immutable/entry/app.DLOf_woB.js","_app/immutable/chunks/scheduler.OWaxIzIJ.js","_app/immutable/chunks/index.3LzlWLC8.js"],"stylesheets":[],"fonts":[],"uses_env_dynamic_public":false},
		nodes: [
			__memo(() => import('./chunks/0-EbCMtCue.js')),
			__memo(() => import('./chunks/1-8dLPTAjr.js')),
			__memo(() => import('./chunks/2-2WJ9O6rK.js')),
			__memo(() => import('./chunks/3-rVaOkHyK.js')),
			__memo(() => import('./chunks/4-4Xq1Yxuj.js')),
			__memo(() => import('./chunks/5-v0G93LKg.js')),
			__memo(() => import('./chunks/6-INCchweE.js')),
			__memo(() => import('./chunks/7-fB--rAp0.js'))
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
