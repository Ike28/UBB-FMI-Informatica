<!DOCTYPE html>
<html>
    <?php 
        function displayGradeTable() {
            header('Access-Control-Allow-Origin: *');
            if (isset($_COOKIE["logged-in"])) {
                echo "<script>console.log('" . $_COOKIE["logged-in"] . "');</script>";
            } else {
                echo "<script>console.log('nono');</script>";
            }
            $conn = new mysqli("localhost", "root", "", "university");
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $username;
            if (isset($_COOKIE["logged-in"])) {
                $username = $_COOKIE["logged-in"];
            }

            $grades = array();
            $subjectIds = array();

            $query = "SELECT idsubject, grade FROM grades WHERE idstudent = (SELECT id FROM students WHERE username = ?);";
            $statement = $conn->prepare($query);
            $statement->bind_param("s", $username);
            $statement->execute();
            $statement->bind_result($idsubject, $grade);

            while ($statement->fetch()) {
                array_push($grades, $grade);
                array_push($subjectIds, $idsubject);
            }

            echo "<table><tr><th>Materie</th><th>Nota</th></tr>";
            for ($i = 0; $i < count($grades); $i++) {
                $ids = $subjectIds[$i];
                $g = $grades[$i];

                $query = "SELECT name FROM subjects WHERE id = ?;";
                $statement = $conn->prepare($query);
                $statement->bind_param("d", $ids);
                $statement->execute();
                $statement->bind_result($name);

                while ($statement->fetch()) {
                    echo "<tr><td>$name</td><td>$g</td></tr>";
                }
            }
            echo "</table>";

            $statement->close();
            $conn->close();
        }
    ?>
    <head>
        <title>Problema 3</title>
        <style>
            table, td, th {
                border: 1px solid black;
            }

        </style>
    </head>
    <body>
        <p>Ai urmatoarele note:</p>
        <br>
        <div id="table-div">
            <?php 
                displayGradeTable();
            ?>
        </div>
    </body>
</html>
