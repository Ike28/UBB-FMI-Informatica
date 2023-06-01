import 'dart:convert';

import 'package:http/http.dart';

class ApiUtils {
  static const String _host = 'localhost';
  static const int _port = 8080;

  static Future<Response> get(final String path) {
    final Client client = Client();
    return client.get(_uri(path));
  }

  static Future<Response> post({required final String path, required final Map<String, String> jsonData}) {
    final Client client = Client();
    return client.post(
      _uri(path),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(jsonData)
    );
  }

  static Future<Response> put({required final String path, required final Map<String, String> jsonData}) {
    final Client client = Client();
    return client.put(
      _uri(path),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(jsonData)
    );
  }

  static Future<Response> delete(final String path) {
    final Client client = Client();
    return client.delete(
        _uri(path),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        }
    );
  }

  static Uri _uri(final String path) {
    return Uri.http('$_host:$_port', path);
  }
}
