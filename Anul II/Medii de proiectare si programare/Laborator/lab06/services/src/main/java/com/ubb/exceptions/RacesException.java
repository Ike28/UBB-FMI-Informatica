package com.ubb.exceptions;

public class RacesException extends Exception {
    public RacesException() {
    }

    public RacesException(String message) {
        super(message);
    }

    public RacesException(String message, Throwable cause) {
        super(message, cause);
    }
}
