package org.example.networking.response;

import java.util.List;

public record IntermediateResponse (List<String> data) implements Response {
}
