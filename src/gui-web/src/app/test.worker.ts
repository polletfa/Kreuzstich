/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

/// <reference lib="webworker" />

addEventListener('message', ({ data }) => {
    const response = `worker response to ${data}`;
    postMessage(response);
});

// declare function WrapperModule(opts?: object): Promise<any>;

// let wasm: any = null;

// async function loadWasm() {
//     importScripts('/assets/wasm/wrapper-wasm.js');
//     wasm = await WrapperModule({
//         locateFile: (file: string) => `/assets/wasm/${file}`
//     });
//     postMessage({ type: 'READY' });
// }

// addEventListener('message', async ({ data }) => {
//     switch (data.type) {

//         case 'INIT':
//             await loadWasm();
//             break;

//         case 'MY_CLASS_GET_X': {
//             const obj = new wasm.MyClass(data.payload.x);
//             const result = obj.getX();
//             obj.delete();
//             postMessage({ type: 'MY_CLASS_GET_X_RESULT', result });
//             break;
//         }

//         case 'ADD': {
//             const result = wasm.add(data.payload.a, data.payload.b);
//             postMessage({ type: 'ADD_RESULT', result });
//             break;
//         }
//     }
// });
