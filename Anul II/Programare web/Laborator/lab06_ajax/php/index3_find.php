<?php 
    header('Access-Control-Allow-Origin: *');
    $conn = new mysqli("localhost", "root", "", "lab6");
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $id = $_GET["id"];
    $query = "SELECT nume, prenume, telefon, email FROM students WHERE id = ?;";
    $statement = $conn->prepare($query);
    $statement->bind_param("d", $id);
    $statement->execute();
    $statement->bind_result($nume, $prenume, $telefon, $email);

    echo "<form>";
    while ($statement->fetch()) {
        echo "<label for='nume'>Nume:</label><br>";
        echo "<input id='nume' name='nume' value=$nume onkeyup='changeFunction()'><br>";

        echo "<label for='prenume'>Prenume:</label><br>";
        echo "<input id='prenume' name='prenume' value=$prenume onkeyup='changeFunction()'><br>";

        echo "<label for='telefon'>Telefon:</label><br>";
        echo "<input id='telefon' name='telefon' value=$telefon onkeyup='changeFunction()'><br>";

        echo "<label for='email'>E-mail:</label><br>";
        echo "<input id='email' name='email' value=$email onkeyup='changeFunction()'><br><br>";
    }
    echo "<input type='submit' id='save-button' value='Save' onclick='saveEntry()' disabled>";
    echo "</form>";

    $conn->close();
?>
