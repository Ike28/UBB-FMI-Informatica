<!DOCTYPE html>
<html>
    <?php 
        header('Access-Control-Allow-Origin: *');
        $conn = new mysqli("localhost", "root", "", "lab7");
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        $query = "SELECT title, content FROM articles;";
        $statement = $conn->prepare($query);
        $statement->execute();
        $statement->bind_result($title, $content);

        while ($statement->fetch()) {
            echo "<p style='border: 1px solid black;'>";
            echo "<h3>$title</h3><br>";
            echo $content;
            echo "</p><br><br>";
        }
    ?>
    <?php 
        function echoCommentForm() {
            echo "<div id='comment-div'>";
            echo "<select id='title-list'>";

            $conn = new mysqli("localhost", "root", "", "lab7");
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $query = "SELECT id, title FROM articles;";
            $statement = $conn->prepare($query);
            $statement->execute();
            $statement->bind_result($id, $title);

            while ($statement->fetch()) {
                echo "<option value='$id'>$title</option>";
            }

            echo "</select><br>";

            echo "<label for='name'>Name:</label>";
            echo "<input type='text' name='name' id='name'><br>";

            echo "<label for='content'>Content:</label>";
            echo "<input type='text' name='content' id='content'><br>";

            echo "<button onclick='postComment()'>Post Comment<br>";

            echo "</div>";
        }
        echoCommentForm();
    ?>
    <?php 
        header('Access-Control-Allow-Origin: *');
        if (isset($_POST["id"]) && isset($_POST["name"]) && isset($_POST["content"])) {
            $conn = new mysqli("localhost", "root", "", "lab7");
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $query = "INSERT INTO comments (idarticle, name, content, approved) VALUES (?, ?, ?, 0);";
            $statement = $conn->prepare($query);
            $statement->bind_param("dss", $_POST["id"], $_POST["name"], $_POST["content"]);
            $statement->execute();
            echo "ok";
        }
    ?>
    <head>
        <title>Problema 6</title>
        <script src="../jquery-min.js"></script>
        <script src="script.js"></script>
        <style>
            input {
                margin: 10px;
            }
            select {
                margin: 10px;
            }

        </style>
    </head>
    <body></body>
</html>
