<?php 
    header('Access-Control-Allow-Origin: *');
    $conn = new mysqli("localhost", "root", "", "lab6");
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $query = "SELECT id FROM students;";
    $result = $conn->query($query);

    echo "<select id='id-list' onchange='findById(this.value)'>";
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            $id = $row["id"];
            echo "<option value='$id'>$id</option>";
        }
    }
    echo "</select>";

    $conn->close();
?>
