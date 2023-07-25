<?php
require_once 'db.php';

// Fetch all parents from the database
if (isset($_GET['string']) && !empty($_GET['string'])) {
    $string = $_GET['string'];

    // Prepare the query to fetch parents with matching children
    $stmt = $conn->prepare("SELECT p.id, p.username, p.dob, GROUP_CONCAT(c.string SEPARATOR ', ') as children
                            FROM parent p
                            LEFT JOIN child c ON p.id = c.idP
                            WHERE c.string LIKE ? 
                            GROUP BY p.id, p.username, p.dob"); // GROUP BY is used to group the children of each parent into a single row
                            // GROUP_CONCAT is used to concatenate the children of each parent into a single string separated by commas
                            //left join is used to return all parents even if they have no children
    $searchString = "%{$string}%";     
    $stmt->bind_param("s", $searchString);
    $stmt->execute();
    $result = $stmt->get_result();
    $parents = $result->fetch_all(MYSQLI_ASSOC);
} else {
    // Fetch all parents if no string is provided
    $stmt = $conn->query("SELECT p.id, p.username, p.dob, GROUP_CONCAT(c.string SEPARATOR ', ') as children
                            FROM parent p
                            LEFT JOIN child c ON p.id = c.idP
                            GROUP BY p.id, p.username, p.dob");
    $parents = $stmt->fetch_All(MYSQLI_ASSOC);
}

// Fetch all children
$childrenStmt = $conn->query("SELECT * FROM child");
$children = $childrenStmt->fetch_All(MYSQLI_ASSOC);
?>

<!DOCTYPE html>
<html>
<head>
  <title>All Parents</title>
  <style>
    table {
      border-collapse: collapse;
      width: 100%;
    }
    th, td {
      border: 1px solid black;
      padding: 8px;
      text-align: center;
    }
  </style>
</head>
<body>
  <h1>All Parents</h1>

  <form method="GET" action="">
    <label for="string">Enter a value for 'string':</label>
    <input type="text" id="string" name="string"> 
    <input type="submit" value="Fetch Children">
  </form>

  <?php if (empty($parents)) { ?>
    <p>No records found.</p>
  <?php } else { ?>
  <table>
    <tr>
      <th>ID</th>
      <th>Name</th>
      <th>dob</th>
      <th>Children</th>
      <th>Actions</th>
    </tr>
    <?php foreach ($parents as $parent) { ?>
    <tr>
      <td><?php echo $parent['id']; ?></td>
      <td><?php echo $parent['username']; ?></td>
      <td><?php echo $parent['dob']; ?></td>
      <!-- this only if in the select we use children count... -->
      <!-- <td><?php //echo $parent['children']; ?></td> -->
      
      <!-- this only if in the selecct stmt we dont use children count.. -->
      <td>
        <?php
        $parentChildren = [];
        foreach ($children as $child) {
            if ($child['idP'] == $parent['id']) {
                $parentChildren[] = $child['string'];
            }
        }
        echo implode(', ', $parentChildren);
        ?>
      </td>
      <td>
        <a href="update.php?id=<?php echo $parent['id']; ?>">Update</a> |
        <a href="delete.php?id=<?php echo $parent['id']; ?>">Delete</a>
      </td>
    </tr>
    <?php } ?>
  </table>
    <?php } ?>
</body>
</html>
