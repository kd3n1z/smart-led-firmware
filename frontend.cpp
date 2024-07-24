// Auto-generated via generate_cpp.sh
// https://github.com/kd3n1z/smart-led-web-gui

#include <ESP8266WebServer.h>
#include "frontend.h"

extern ESP8266WebServer server;

void SETUP_FRONTEND_SERVER() {
  server.on("/gui/assets/index-7MVG7eJ9.css", []() {
    server.send(200, "text/css", "html,body{margin:0;min-height:100%}body{font-family:Inter,system-ui,Avenir,Helvetica,Arial,sans-serif;background:#181818;color:#fff}main{position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);padding:30px;background:#202020;border-radius:15px;min-width:300px;display:flex;flex-direction:column}\n");
  });
  server.on("/gui/assets/index-SFkHWZyB.js", []() {
    server.send(200, "application/javascript", "var R=Object.defineProperty;var q=(e,t,n)=>t in e?R(e,t,{enumerable:!0,configurable:!0,writable:!0,value:n}):e[t]=n;var m=(e,t,n)=>q(e,typeof t!=\"symbol\"?t+\"\":t,n);(function(){const t=document.createElement(\"link\").relList;if(t&&t.supports&&t.supports(\"modulepreload\"))return;for(const r of document.querySelectorAll('link[rel=\"modulepreload\"]'))o(r);new MutationObserver(r=>{for(const i of r)if(i.type===\"childList\")for(const s of i.addedNodes)s.tagName===\"LINK\"&&s.rel===\"modulepreload\"&&o(s)}).observe(document,{childList:!0,subtree:!0});function n(r){const i={};return r.integrity&&(i.integrity=r.integrity),r.referrerPolicy&&(i.referrerPolicy=r.referrerPolicy),r.crossOrigin===\"use-credentials\"?i.credentials=\"include\":r.crossOrigin===\"anonymous\"?i.credentials=\"omit\":i.credentials=\"same-origin\",i}function o(r){if(r.ep)return;r.ep=!0;const i=n(r);fetch(r.href,i)}})();function d(){}function P(e){return e()}function I(){return Object.create(null)}function _(e){e.forEach(P)}function C(e){return typeof e==\"function\"}function B(e,t){return e!=e?t==t:e!==t||e&&typeof e==\"object\"||typeof e==\"function\"}function T(e){return Object.keys(e).length===0}function $(e,t){e.appendChild(t)}function U(e,t,n){e.insertBefore(t,n||null)}function j(e){e.parentNode&&e.parentNode.removeChild(e)}function y(e){return document.createElement(e)}function M(e){return document.createTextNode(e)}function D(e,t,n,o){return e.addEventListener(t,n,o),()=>e.removeEventListener(t,n,o)}function F(e,t,n){e.getAttribute(t)!==n&&e.setAttribute(t,n)}function G(e){return Array.from(e.childNodes)}let v;function g(e){v=e}const a=[],N=[];let h=[];const S=[],K=Promise.resolve();let w=!1;function V(){w||(w=!0,K.then(A))}function x(e){h.push(e)}const b=new Set;let l=0;function A(){if(l!==0)return;const e=v;do{try{for(;l<a.length;){const t=a[l];l++,g(t),W(t.$$)}}catch(t){throw a.length=0,l=0,t}for(g(null),a.length=0,l=0;N.length;)N.pop()();for(let t=0;t<h.length;t+=1){const n=h[t];b.has(n)||(b.add(n),n())}h.length=0}while(a.length);for(;S.length;)S.pop()();w=!1,b.clear(),g(e)}function W(e){if(e.fragment!==null){e.update(),_(e.before_update);const t=e.dirty;e.dirty=[-1],e.fragment&&e.fragment.p(e.ctx,t),e.after_update.forEach(x)}}function z(e){const t=[],n=[];h.forEach(o=>e.indexOf(o)===-1?t.push(o):n.push(o)),n.forEach(o=>o()),h=t}const H=new Set;function J(e,t){e&&e.i&&(H.delete(e),e.i(t))}function Q(e,t,n){const{fragment:o,after_update:r}=e.$$;o&&o.m(t,n),x(()=>{const i=e.$$.on_mount.map(P).filter(C);e.$$.on_destroy?e.$$.on_destroy.push(...i):_(i),e.$$.on_mount=[]}),r.forEach(x)}function X(e,t){const n=e.$$;n.fragment!==null&&(z(n.after_update),_(n.on_destroy),n.fragment&&n.fragment.d(t),n.on_destroy=n.fragment=null,n.ctx=[])}function Y(e,t){e.$$.dirty[0]===-1&&(a.push(e),V(),e.$$.dirty.fill(0)),e.$$.dirty[t/31|0]|=1<<t%31}function Z(e,t,n,o,r,i,s=null,p=[-1]){const f=v;g(e);const c=e.$$={fragment:null,ctx:[],props:i,update:d,not_equal:r,bound:I(),on_mount:[],on_destroy:[],on_disconnect:[],before_update:[],after_update:[],context:new Map(t.context||(f?f.$$.context:[])),callbacks:I(),dirty:p,skip_bound:!1,root:t.target||f.$$.root};s&&s(c.root);let E=!1;if(c.ctx=n?n(e,t.props||{},(u,O,...L)=>{const k=L.length?L[0]:O;return c.ctx&&r(c.ctx[u],c.ctx[u]=k)&&(!c.skip_bound&&c.bound[u]&&c.bound[u](k),E&&Y(e,u)),O}):[],c.update(),E=!0,_(c.before_update),c.fragment=o?o(c.ctx):!1,t.target){if(t.hydrate){const u=G(t.target);c.fragment&&c.fragment.l(u),u.forEach(j)}else c.fragment&&c.fragment.c();t.intro&&J(e.$$.fragment),Q(e,t.target,t.anchor),A()}g(f)}class ee{constructor(){m(this,\"$$\");m(this,\"$$set\")}$destroy(){X(this,1),this.$destroy=d}$on(t,n){if(!C(n))return d;const o=this.$$.callbacks[t]||(this.$$.callbacks[t]=[]);return o.push(n),()=>{const r=o.indexOf(n);r!==-1&&o.splice(r,1)}}$set(t){this.$$set&&!T(t)&&(this.$$.skip_bound=!0,this.$$set(t),this.$$.skip_bound=!1)}}const te=\"4\";typeof window<\"u\"&&(window.__svelte||(window.__svelte={v:new Set})).v.add(te);function ne(e){let t,n,o,r,i,s;return{c(){t=y(\"main\"),n=M(`Smart LED Web GUI\n\n    `),o=y(\"div\"),r=y(\"input\"),F(r,\"type\",\"color\")},m(p,f){U(p,t,f),$(t,n),$(t,o),$(o,r),i||(s=D(r,\"change\",e[0]),i=!0)},p:d,i:d,o:d,d(p){p&&j(t),i=!1,s()}}}function re(e){const t=oe(e);t!=null&&ie(`set-solid-color ${t.r} ${t.g} ${t.b}`)}function oe(e){const t=/^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i.exec(e);return t?{r:parseInt(t[1],16),g:parseInt(t[2],16),b:parseInt(t[3],16)}:null}function ie(...e){const t=e.join(\";\");console.log(\"making api request: \"+t),fetch(window.location.origin+\"/api\"+new URLSearchParams({commands:t}))}function ce(e){return[n=>re(n.currentTarget.value)]}class se extends ee{constructor(t){super(),Z(this,t,ce,ne,B,{})}}new se({target:document.getElementById(\"app\")});\n");
  });
  server.on("/gui/", []() {
    server.sendHeader("Location", String("/gui/index.html"), true);
    server.send(302, "text/plain", "");
  });
  server.on("/gui/index.html", []() {
    server.send(200, "text/html", "<!doctype html>\n<html lang=\"en\">\n  <head>\n    <meta charset=\"UTF-8\" />\n    <link rel=\"icon\" type=\"image/svg+xml\" href=\"/gui/vite.svg\" />\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n    <title>Vite + Svelte + TS</title>\n    <script type=\"module\" crossorigin src=\"/gui/assets/index-SFkHWZyB.js\"></script>\n    <link rel=\"stylesheet\" crossorigin href=\"/gui/assets/index-7MVG7eJ9.css\">\n  </head>\n  <body>\n    <div id=\"app\"></div>\n  </body>\n</html>\n");
  });
  server.on("/gui/vite.svg", []() {
    server.send(200, "image/svg+xml", "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" aria-hidden=\"true\" role=\"img\" class=\"iconify iconify--logos\" width=\"31.88\" height=\"32\" preserveAspectRatio=\"xMidYMid meet\" viewBox=\"0 0 256 257\"><defs><linearGradient id=\"IconifyId1813088fe1fbc01fb466\" x1=\"-.828%\" x2=\"57.636%\" y1=\"7.652%\" y2=\"78.411%\"><stop offset=\"0%\" stop-color=\"#41D1FF\"></stop><stop offset=\"100%\" stop-color=\"#BD34FE\"></stop></linearGradient><linearGradient id=\"IconifyId1813088fe1fbc01fb467\" x1=\"43.376%\" x2=\"50.316%\" y1=\"2.242%\" y2=\"89.03%\"><stop offset=\"0%\" stop-color=\"#FFEA83\"></stop><stop offset=\"8.333%\" stop-color=\"#FFDD35\"></stop><stop offset=\"100%\" stop-color=\"#FFA800\"></stop></linearGradient></defs><path fill=\"url(#IconifyId1813088fe1fbc01fb466)\" d=\"M255.153 37.938L134.897 252.976c-2.483 4.44-8.862 4.466-11.382.048L.875 37.958c-2.746-4.814 1.371-10.646 6.827-9.67l120.385 21.517a6.537 6.537 0 0 0 2.322-.004l117.867-21.483c5.438-.991 9.574 4.796 6.877 9.62Z\"></path><path fill=\"url(#IconifyId1813088fe1fbc01fb467)\" d=\"M185.432.063L96.44 17.501a3.268 3.268 0 0 0-2.634 3.014l-5.474 92.456a3.268 3.268 0 0 0 3.997 3.378l24.777-5.718c2.318-.535 4.413 1.507 3.936 3.838l-7.361 36.047c-.495 2.426 1.782 4.5 4.151 3.78l15.304-4.649c2.372-.72 4.652 1.36 4.15 3.788l-11.698 56.621c-.732 3.542 3.979 5.473 5.943 2.437l1.313-2.028l72.516-144.72c1.215-2.423-.88-5.186-3.54-4.672l-25.505 4.922c-2.396.462-4.435-1.77-3.759-4.114l16.646-57.705c.677-2.35-1.37-4.583-3.769-4.113Z\"></path></svg>\n");
  });
}
