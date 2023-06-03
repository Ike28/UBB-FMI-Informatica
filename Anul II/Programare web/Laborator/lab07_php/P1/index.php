<!DOCTYPE html>
<html>
<?php 
    function handleForm() {
        if (isset($_GET["cursa"]) && isset($_GET["plecare"]) && isset($_GET["sosire"])) {
            header('Access-Control-Allow-Origin: *');
            $conn = new mysqli("localhost", "root", "", "lab7");
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $direct = $_GET["cursa"];
            $plecare = $_GET["plecare"];
            $sosire = $_GET["sosire"];
            if ($direct == "direct") {
                $direct = true;
            } else {
                $direct = false;
            }

            $statement;
            if ($direct == "true") {
                $query =    "SELECT * FROM routes 
                            WHERE plecare = ? 
                            AND sosire = ?;";

                $statement = $conn->prepare($query);
                $statement->bind_param("ss", $plecare, $sosire);
                $statement->execute();
                $statement->bind_result($nrtren, $tiptren, $plecare, $sosire, $oraplecare, $orasosire);

                $noRows = 0;
                while ($statement->fetch()) {
                    echo "<p>Traseu Direct:<br>Numar Tren: $nrtren <br>Tip Tren: $tiptren <br><b>Gara Plecare: $plecare </b><br>
                    <b>Gara Sosire: $sosire </b><br>Ora Plecare: $oraplecare <br>Ora Sosire: $orasosire</p><br><br>";
                    $noRows++;
                }

                if ($noRows == 0) {
                    echo "<p>Nu exista curse directe intre $plecare si $sosire!</p>";
                }
            } else {
                $query =    "SELECT * FROM routes WHERE plecare = ? AND sosire = ?;";
                $statement = $conn->prepare($query);
                $statement->bind_param("ss", $plecare, $sosire);
                $statement->execute();
                $statement->bind_result($nrtren, $tiptren, $plecare, $sosire, $oraplecare, $orasosire);

                $noRows = 0;
                while ($statement->fetch()) {
                    echo "<p>Traseu Direct:<br>Numar Tren: $nrtren <br>Tip Tren: $tiptren <br><b>Gara Plecare: $plecare </b><br>
                    <b>Gara Sosire: $sosire </b><br>Ora Plecare: $oraplecare <br>Ora Sosire: $orasosire</p><br><br>";
                    $noRows++;
                }

                $query = "SELECT * FROM routes r1, routes r2 WHERE r1.plecare = ? AND r2.sosire = ? AND r1.sosire = r2.plecare AND r2.oraplecare > r1.orasosire;";
                $statement = $conn->prepare($query);
                $statement->bind_param("ss", $plecare, $sosire);
                $statement->execute();
                $statement->bind_result($nrtren1, $tiptren1, $plecare1, $sosire1, $oraplecare1, $orasosire1, $nrtren2, $tiptren2, $plecare2, $sosire2, $oraplecare2, $orasosire2);

                while ($statement->fetch()) {                    
                    echo "<p>Traseu 1:<br>Numar Tren: $nrtren1 <br>Tip Tren: $tiptren1 <br><b>Gara Plecare: $plecare1 </b><br>
                    <b>Gara Sosire: $sosire1 </b><br>Ora Plecare: $oraplecare1 <br>Ora Sosire: $orasosire1 <br><br>Traseu 2:<br>Numar Tren: $nrtren2 <br>Tip Tren: $tiptren2 <br><b>Gara Plecare: $plecare2 </b><br>
                    <b>Gara Sosire: $sosire2 </b><br>Ora Plecare: $oraplecare2 <br>Ora Sosire: $orasosire2</p><br><br><br>";
                    $noRows++;
                }

                if ($noRows == 0) {
                    echo "<p>Nu exista curse intre $plecare si $sosire!</p>";
                }
            }

            $statement->close();
            $conn->close();
        }
    }
?>
<head>
    <title>Problema 1</title>
    <style>
        .form {
            margin: 10px;
        }

        input, label, button {
            margin: 10px;
        }

    </style>
</head>
<body>
    <div class="form">
        <form action="index.php" method="GET">
                <label for="plecare">Gara de Plecare</label>
                <input type="text" name="plecare" id="plecare"><br>

                <label for="sosire">Gara de Sosire</label>
                <input type="text" name="sosire" id="sosire"><br>

                <label for="direct">Curse Directe</label>
                <input type="radio" id="direct" name="cursa" value="direct">

                <label for="legatura">Curse cu Legatura</label>
                <input type="radio" id="legatura" name="cursa" value="legatura"><br>

                <input type="submit" value="Cauta">
        </form>
    </div>
    <div id="result">
        <?php
            handleForm();
        ?>
    </div>
</body>
</html>
