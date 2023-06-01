import 'dart:convert';

import 'package:http/http.dart';

import '../api_utils.dart';
import '../models/race.dart';

class RacesApi {
  static Future<List<Race>> getRaces() async {
    final Response response = await ApiUtils.get('/contest/races');
    final List<Race> results = <Race>[];

    if (response.statusCode == 200) {
      final List<dynamic> data = jsonDecode(response.body) as List<dynamic>;

      for (int i = 0; i < data.length; i++) {
        final Map<String, dynamic> race = data[i] as Map<String, dynamic>;
        final Race item = Race(
            id: race['id'] as int,
            name: race['name'] as String,
            engineCapacity: race['engineCapacity'] as int);
        results.add(item);
      }
    }
    return results;
  }

  static Future<Race?> getRaceById({required String id}) async {
    final Response response = await ApiUtils.get('/contest/races/$id');

    if (response.statusCode == 404) {
      return null;
    }

    if (response.statusCode == 200) {
      final Map<String, dynamic> race = jsonDecode(response.body) as Map<
          String,
          dynamic>;

      final Race item = Race(
          id: race['id'] as int,
          name: race['name'] as String,
          engineCapacity: race['engineCapacity'] as int);
      return item;
    }
    return null;
  }

  static Future<int> createRace({required String name, required String capacity}) async {
    final Response response = await ApiUtils.post(
      path: '/contest/races',
      jsonData: <String, String>{
        'name': name,
        'engineCapacity': capacity
      }
    );

    return response.statusCode;
  }

  static Future<int> updateRace({required String id, required String name, required String capacity}) async {
    final Response response = await ApiUtils.put(
      path: '/contest/races/$id',
      jsonData: <String, String>{
        'id': id,
        'name': name,
        'engineCapacity': capacity
      });

    return response.statusCode;
  }

  static Future<int> deleteRace({required String id}) async {
    final Response response = await ApiUtils.delete('/contest/races/$id');

    return response.statusCode;
  }
}
