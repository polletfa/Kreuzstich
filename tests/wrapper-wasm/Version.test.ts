/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

// Note: we only check the bindings, not the functionality, which is tested directly in the core component.

import { describe, it, expect, beforeAll, beforeEach, afterEach } from 'vitest';
import * as Core from './build/wrapper-wasm';

let core: Core.Module;

beforeAll(async () => {
    core = await Core.load();
});

describe('Version', () => {
    it('NAME', () => {
        expect(core.Version.NAME).not.toBeUndefined();
    });

    it('WEBSITE', () => {
        expect(core.Version.WEBSITE).not.toBeUndefined();
    });

    it('MAJOR', () => {
        expect(core.Version.MAJOR).not.toBeUndefined();
    });

    it('MINOR', () => {
        expect(core.Version.MINOR).not.toBeUndefined();
    });

    it('BUILD_TIME', () => {
        expect(core.Version.BUILD_TIME).not.toBeUndefined();
    });

    it('GIT_COMMIT', () => {
        expect(core.Version.GIT_COMMIT).not.toBeUndefined();
    });

    it('RELEASE_BUILD', () => {
        expect(core.Version.RELEASE_BUILD).not.toBeUndefined();
    });

    it('LICENSE', () => {
        expect(core.Version.LICENSE).not.toBeUndefined();
    });

    it('getVersionString', () => {
        expect(core.Version.getVersionString()).not.toBeUndefined();
    });

    it('replaceVersionVars', () => {
        expect(core.Version.replaceVersionVars("_$NAME$_")).toBe("_Kreuzstich_");
    });
});
