<!DOCTYPE html>
<html>
    <?php 
        function displaySelects() {
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

            $query = "SELECT id, name FROM students;";
            $statement = $conn->prepare($query);
            $statement->execute();
            $statement->bind_result($id, $name);

            echo "<select name='student'>";
            while ($statement->fetch()) {
                echo "<option value='$id'>$name</option>";
            }

            echo "</select>";
            $query = "SELECT id, name FROM subjects;";
            $statement = $conn->prepare($query);
            $statement->execute();
            $statement->bind_result($id, $name);

            echo "<select name='subject'>";
            while ($statement->fetch()) {
                echo "<option value='$id'>$name</option>";
            }
            echo "</select>";

            $statement->close();
            $conn->close();
        }
    ?>
    <?php 
        function handleAddGradeRequest() {
            if (isset($_GET["student"]) && isset($_GET["subject"]) && isset($_GET["grade"])) {
                header('Access-Control-Allow-Origin: *');
                $conn = new mysqli("localhost", "root", "", "university");
                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                }

                $student = $_GET["student"];
                $subject = $_GET["subject"];
                $grade = $_GET["grade"];
                if (!((double) $grade >= 1 && (double) $grade <= 10)) {
                    echo "<p style='color: red;'>Nota invalida!</p>";
                } else {
                    $query = "INSERT INTO grades(idstudent, idsubject, grade) VALUES (?, ?, ?);";
                    $statement = $conn->prepare($query);
                    $statement->bind_param("ddd", $student, $subject, $grade);
                    $statement->execute();
                    echo "<p style='color: green;'>Nota adaugata cu succes!</p>";

                    $statement->close();
                    $conn->close();
                }
            }
        }
    ?>
    <head>
        <title>Problema 3</title>
        <style>
            input {
                margin: 10px;
            }

            select {
                margin: 10px;
            }

        </style>
    </head>
    <body>
        <div id="result">
            <?php 
                handleAddGradeRequest();
            ?>
        </div>
        <form action="teacher.php" method="GET">
            <?php
                displaySelects();
            ?>
            <label for="grade">Nota</label>
            <input type="text" name="grade" id="grade">

            <input type="submit" value="Adaugare Nota">
        </form>
        <br>
        <div id="response"></div>
    </body>
</html>
