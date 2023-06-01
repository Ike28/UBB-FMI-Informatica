import 'package:flutter/material.dart';

import 'homepage.dart';

void main() async {
  runApp(const PhotosApp());
}

class PhotosApp extends StatelessWidget {
  const PhotosApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'MXGP Races portal',
      theme: ThemeData.dark(),
      home: const HomePage(),
    );
  }
}
