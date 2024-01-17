package org.example.networking.request;

public record SendPointsRequest (
        String country,
        String[] data
) implements Request {
}
