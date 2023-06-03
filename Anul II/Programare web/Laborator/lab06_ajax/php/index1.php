<?php
    header('Access-Control-Allow-Origin: *');
    $conn = new mysqli("localhost", "root", "", "lab6");

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $departure = $_GET["departure"];
    $query = "SELECT arrival FROM routes WHERE departure = ?;";
    $statement = $conn->prepare($query);
    $statement->bind_param("s", $departure);
    $statement->execute();
    $statement->bind_result($result);

    echo "<select id='arrival-list' multiple='true'>";
    while($statement->fetch()) {
        echo "<option value='" . $result .  "'>" . $result ."</option>";
    }
    echo "</select>";

    $statement->close();
    $conn->close();
?>
