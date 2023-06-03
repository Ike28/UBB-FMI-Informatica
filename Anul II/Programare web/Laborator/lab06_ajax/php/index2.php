<?php
    header('Access-Control-Allow-Origin: *');
    $conn = new mysqli("localhost", "root", "", "lab6");
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $pageNumber = $_GET["page"];
    $query = "SELECT * FROM students;";
    $result = $conn->query($query);

    $entries = 0;
    $moreEntries = false;
    echo "<table><tr><th>Nume</th><th>Prenume</th><th>Telefon</th><th>E-mail</th></tr>";
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            if ($entries >= $pageNumber * 3) {
                if ($entries < ($pageNumber + 1) * 3) {
                    echo "<tr>";
                    echo "<td>" . $row["nume"] . "</td>";
                    echo "<td>" . $row["prenume"] . "</td>";
                    echo "<td>" . $row["telefon"] . "</td>";
                    echo "<td>" . $row["email"] . "</td>";
                    echo "</tr>";
                } else {
                    $moreEntries = true;
                }
            }
            $entries++;
        }
    }

    echo "</table>";
    if ($pageNumber == 0) {
        echo "<button disabled>Previous</button>";
    } else {
        echo "<button onclick='previousPage()'>Previous</button>";
    }
    
    if ($moreEntries) {
        echo "<button onclick='nextPage()'>Next</button>";
    } else {
        echo "<button disabled>Next</button>";
    }

    $conn->close();
?>
