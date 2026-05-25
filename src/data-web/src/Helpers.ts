/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

export class Helpers {
    /**
     * Helper method to log error message: create a loggable string from an error object.
     *
     * This method should be used to log error objects (for example from database exceptions), to ensure that only the message is logged
     * and not the whole object, which may contain user data. This is a requirement from the Data Processing Guidelines.
     *
     * @param error Error object - If the object has a string property "message", the message is returned. Otherwise, only "unknown" is returned.
     */
    public static errorToString(error: unknown): string {
        if(typeof error === 'object' && error !== null && 'message' in error && typeof error.message === 'string') {
            return error.message;
        } else {
            return 'unknown';
        }
    }
}
