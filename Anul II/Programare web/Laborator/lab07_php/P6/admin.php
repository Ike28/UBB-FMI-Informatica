<?php
    header('Access-Control-Allow-Origin: *');
    $conn = new mysqli("localhost", "root", "", "lab7");
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $query = "SELECT name, content, approved FROM comments;";
    $statement = $conn->prepare($query);
    $statement->execute();
    $statement->bind_result($name, $content, $approved);

    echo "<table id='table'><tr><th>Name</th><th>Content</th><th>Approve</th></tr>";
    while ($statement->fetch()) {
        echo "<tr>";

        echo "<td>$name</td>";
        echo "<td>$content</td>";
        if ($approved == 1) {
            echo "<td><input type='checkbox' checked></td>";
        } else {
            echo "<td><input type='checkbox'></td>";
        }

        echo "</tr>";
    }
    echo "</table><br>";
    echo "<button onclick='approve()'>Submit</button>";
?>
<!DOCTYPE html>
<html>
    <head>
        <title>Administrator</title>
        <script src="../jquery-min.js"></script>
        <script src="script.js"></script>
        <style>
            table, th, td {
                border: 1px solid black;
            }

        </style>
    </head>
</html>
