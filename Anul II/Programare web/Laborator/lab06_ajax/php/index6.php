<?php 
    header("Access-Control-Allow-Origin: *");
    $conn = new mysqli("localhost", "root", "", "lab6");

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $keyword = $_GET["keyword"];
    $crit = $_GET["crit"];

    $query;
    $statement;
    if ($crit == "memorie" || $crit == "capacitatehdd") {
        if ($keyword != "") {
            $query = "SELECT * FROM products WHERE $crit = ?;";
            $statement = $conn->prepare($query);
            $statement->bind_param("d", $keyword);
        } else {
            $query = "SELECT * FROM products;";
            $statement = $conn->prepare($query);
        }
    } else {
        $query = "SELECT * FROM products WHERE $crit LIKE '%$keyword%';";
        $statement = $conn->prepare($query);
    }

    $statement->execute();
    $statement->bind_result($producator, $procesor, $memorie, $capacitatehdd, $placavideo);

    echo "<table><tr><th>Producator</th><th>Procesor</th><th>Memorie</th><th>Capacitate HDD</th><th>Placa Video</th></tr>";

    while ($statement->fetch()) {
        echo "<tr>";
        echo "<td>$producator</td>";
        echo "<td>$procesor</td>";
        echo "<td>$memorie</td>";
        echo "<td>$capacitatehdd</td>";
        echo "<td>$placavideo</td>";
        echo "</tr>";
    }
    echo "</table>";
?>
