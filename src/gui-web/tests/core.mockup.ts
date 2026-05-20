/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Version } from '@version';

const mockThread = class {
    delete = vi.fn();
    [Symbol.dispose]() { this.delete(); }
    name = vi.fn().mockReturnValue("mock");
}
export const mockCore = {
    Version: {
        getVersionString: vi.fn().mockReturnValue(Version.getVersionString())
    },
    ColorSpace: {
        compositeRGBAOntoBackground: vi.fn(),
        distance: vi.fn()
    },
    Thread: mockThread,
    ThreadList: class {
        delete = vi.fn();
        [Symbol.dispose]() { this.delete(); }

        get = vi.fn().mockReturnValue([
            new mockThread(),
            new mockThread()
        ]);
        findClosest = vi.fn().mockReturnValue(new mockThread());
    }
};
