<?php 
    header('Access-Control-Allow-Origin: *');
    $conn = new mysqli("localhost", "root", "", "lab6");
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $id = $_GET["id"];
    $nume = $_GET["nume"];
    $prenume = $_GET["prenume"];
    $telefon = $_GET["telefon"];
    $email = $_GET["email"];

    $query = "UPDATE students SET nume = ?, prenume = ?, telefon = ?, email = ? WHERE id = ?;";
    $statement = $conn->prepare($query);
    $statement->bind_param("ssssd", $nume, $prenume, $telefon, $email, $id);
    $statement->execute();

    $conn->close();
?>
