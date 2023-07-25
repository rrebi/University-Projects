<?php
require_once 'db.php';

// Fetch all parents from the database
$stmt = $conn->query("SELECT parent.*, COUNT(child.id) AS number_of_children
                     FROM parent
                     LEFT JOIN child ON parent.id = child.idP
                     GROUP BY parent.id");
$parents = $stmt->fetch_all(MYSQLI_ASSOC);

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
  <table>
    <tr>
      <th>ID</th>
      <th>Name</th>
      <th>Email</th>
      <th>Number of Children</th>
      <th>Actions</th>
    </tr>
    <?php foreach ($parents as $parent) { ?>
    <tr>
      <td><?php echo $parent['id']; ?></td> 
      <td><?php echo $parent['username']; ?></td>
      <td><?php echo $parent['dob']; ?></td>
      <td><?php echo $parent['number_of_children']; ?></td>
      <td>
        <a href="updateP.php?id=<?php echo $parent['id']; ?>">Update</a> |
        <a href="deleteP.php?id=<?php echo $parent['id']; ?>">Delete</a>
      </td>
    </tr>
    <?php } ?>
  </table>
</body>
</html>
