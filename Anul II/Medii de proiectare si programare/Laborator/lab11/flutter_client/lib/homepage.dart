import 'dart:js_interop';

import 'package:flutter/material.dart';

import 'api/races_api.dart';
import 'models/race.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final List<Race> _races = <Race>[];
  final TextEditingController _searchController = TextEditingController();
  final TextEditingController _nameController = TextEditingController();
  final TextEditingController _capacityController = TextEditingController();
  bool _isLoading = false;
  bool _updating = false;
  String _searchQuery = '';

  @override
  void initState() {
    super.initState();
    _setRaces();
  }

  Future<void> _setRaces() async {
    setState(() {
      _isLoading = true;
      _races.clear();
    });

    _races.addAll(await RacesApi.getRaces());

    setState(() {
      _isLoading = false;
    });
  }

  Future<void> _setSearchedRace({required String id}) async {
    setState(() {
      _isLoading = true;
      _races.clear();
    });

    final Race? found = await RacesApi.getRaceById(id: id);
    if (found.isNull) {
      setState(() {
        _isLoading = false;
      });
    } else {
      setState(() {
        _races.add(found!);
        _isLoading = false;
      });
    }
  }

  Future<void> _createRace({required String name, required String capacity}) async {
    setState(() {
      _isLoading = true;
    });

    final int responseCode = await RacesApi.createRace(name: name, capacity: capacity);
    if (responseCode == 200) {
      setState(() {
        _isLoading = false;
        _setRaces();
      });
    }
  }

  Future<void> _updateRace({required String id, required String name, required String capacity}) async {
    setState(() {
      _isLoading = true;
      _updating = true;
    });

    final int responseCode = await RacesApi.updateRace(id: id, name: name, capacity: capacity);
    if (responseCode == 200) {
      setState(() {
        _isLoading = false;
        _updating = false;
        _setRaces();
      });
    }
  }

  Future<void> _deleteRace({required String id}) async {
    setState(() {
      _isLoading = true;
      _updating = true;
    });

    final int responseCode = await RacesApi.deleteRace(id: id);
    if (responseCode == 200) {
      setState(() {
        _isLoading = false;
        _updating = false;
        _setRaces();
      });
    }
  }

  bool _validateData() {
    if (_nameController.text.isEmpty || _capacityController.text.isEmpty) {
      setState(() {
        showDialog(
            context: context,
            builder: (BuildContext context) {
              return AlertDialog(
                title: const Text('Input errors detected!'),
                content: const Column(
                  children: <Text>[
                    Text('Race name cannot be empty'),
                    Text('Engine capacity must be a strictly positive integer')
                  ],
                ),
                actions: <Widget>[
                  TextButton(
                      onPressed: () {
                        Navigator.of(context).pop();
                      },
                      child: const Text('OK')
                  )
                ],
              );
            });
      });
      return false;
    }
    return true;
  }

  void _showUpdateMenu({required int id, required String name, required int capacity}) {
    setState(() {
      _updating = true;
      showDialog(
          context: context,
          builder: (BuildContext context) {
            _nameController.text = name;
            _capacityController.text = capacity.toString();
            return AlertDialog(
              title: const Text('Update race'),
              content: Column(
                children: <Widget>[
                  Text('id #$id'),
                  TextField(
                    controller: _nameController,
                    decoration: const InputDecoration(
                        hintText: 'Race name...'
                    ),
                  ),
                  TextField(
                    controller: _capacityController,
                    decoration: const InputDecoration(
                        hintText: 'Engine capacity...'
                    ),
                    keyboardType: TextInputType.number,
                  )
                ],
              ),
              actions: <Widget>[
                TextButton(
                    onPressed: () {
                      _updating = false;
                      Navigator.of(context).pop();
                      if (_validateData()) {
                        final String name = _nameController
                            .text;
                        final String capacity = _capacityController
                            .text;
                        _updateRace(
                            id: id.toString(), name: name, capacity: capacity);
                      }
                    },
                    child: const Text('Submit')
                ),
                TextButton(
                    onPressed: () {
                      _updating = false;
                      Navigator.of(context).pop();
                      _deleteRace(id: id.toString());
                    },
                    child: const Text('Delete')
                ),
                TextButton(
                    onPressed: () {
                      _updating = false;
                      Navigator.of(context).pop();
                    },
                    child: const Text('Cancel')
                )
              ],
            );
          });
    });
  }

  void _showCreateMenu() {
    if (_updating) {
      return;
    }
    setState(() {
      _updating = true;
      showDialog(
          context: context,
          builder: (BuildContext context) {
            return AlertDialog(
              title: const Text('Create race'),
              content: Column(
                children: <TextField>[
                  TextField(
                    controller: _nameController,
                    decoration: const InputDecoration(
                        hintText: 'Race name...'
                    ),
                  ),
                  TextField(
                    controller: _capacityController,
                    decoration: const InputDecoration(
                        hintText: 'Engine capacity...'
                    ),
                    keyboardType: TextInputType.number,
                  )
                ],
              ),
              actions: <Widget>[
                TextButton(
                    onPressed: () {
                      _updating = false;
                      Navigator.of(context).pop();
                      if (_validateData()) {
                        final String name = _nameController
                            .text;
                        final String capacity = _capacityController
                            .text;
                        _createRace(
                            name: name, capacity: capacity);
                      }
                    },
                    child: const Text('Submit')
                ),
                TextButton(
                    onPressed: () {
                      _updating = false;
                      Navigator.of(context).pop();
                    },
                    child: const Text('Cancel')
                )
              ],
            );
          });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('MXGP - Races'),
          actions: <Widget>[
            if (_isLoading)
              const Center(
                child: FittedBox(
                  child: Padding(
                    padding: EdgeInsets.all(16),
                    child: CircularProgressIndicator(),
                  ),
                ),
              )
          ],
        ),
        body: _isLoading
            ? const Center(
          child: CircularProgressIndicator(),
        )
            : Column(
          children: <Widget>[
            Row(
              children: <Widget>[
                Expanded(
                    child: TextField(
                      controller: _searchController,
                      decoration: const InputDecoration(
                          label: Text('Search by id...'),
                          prefixIcon: Icon(Icons.search),
                          prefixIconColor: Colors.lightBlue),
                    )),
                TextButton(
                    onPressed: () {
                      _searchQuery = _searchController.text;
                      if (_searchQuery.isEmpty) {
                        _setRaces();
                      } else {
                        _setSearchedRace(id: _searchQuery);
                      }
                    },
                    style: TextButton.styleFrom(backgroundColor: Colors.lightBlue, foregroundColor: Colors.white),
                    child: const Text('Search')),
                TextButton(
                    onPressed: () {
                      _showCreateMenu();
                    }, child: const Text('Create'))
              ],
            ),
            const SizedBox(
              height: 10,
            ),
            Expanded(
              child: _races.isNotEmpty
                  ? GridView.builder(
                  itemCount: _races.length,
                  gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(crossAxisCount: 4),
                  itemBuilder: (BuildContext context, int index) {
                    final Race race = _races[index];
                    return Stack(fit: StackFit.expand, children: <Widget>[
                      Align(
                          alignment: AlignmentDirectional.bottomEnd,
                          child: Container(
                            decoration: const BoxDecoration(
                                gradient: LinearGradient(
                                    begin: AlignmentDirectional.bottomCenter,
                                    end: AlignmentDirectional.topCenter,
                                    colors: <Color>[Colors.black, Colors.transparent])),
                            child: ListTile(
                              title: Text('${race.name} (${race.engineCapacity}cc)'),
                              subtitle: Text('id #${race.id}'),
                              onTap: () {
                                _showUpdateMenu(id: race.id, name: race.name, capacity: race.engineCapacity);
                              },
                            ),
                          ))
                    ]);
                  })
                  : const Center(
                child: CircularProgressIndicator(semanticsLabel: 'Loading races...'),
              ),
            )
          ],
        ));
  }
}
