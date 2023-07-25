using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Lab1
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter daParent;
        SqlDataAdapter daChild;
        DataSet dset;


        BindingSource bsParent;
        BindingSource bsChild;

        SqlCommandBuilder cmdBuilder;

        string queryParent;
        string queryChild;

        public Form1()
        {
            InitializeComponent();
            FillData();
            //this.dataGridView2.CellValidating += new DataGridViewCellValidatingEventHandler(dataGridView2_CellValidating);

        }

        private void dataGridView2_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            if (e.ColumnIndex == 0) // ID column
            {
                int id;
                if (!int.TryParse(e.FormattedValue.ToString(), out id))
                {
                    e.Cancel = true;
                    MessageBox.Show("The ID must be a valid integer.");
                }
            }
        }

        void FillData()
        {
            //sqlConnection
            conn = new SqlConnection(getConnectionString());

            queryParent = "SELECT * FROM Client"; 
            queryChild = "SELECT * FROM MedicalImage";

            //SqlDataAdapter, DataSet
            daParent = new SqlDataAdapter(queryParent, conn);
            daChild = new SqlDataAdapter(queryChild, conn);
            dset = new DataSet();
            daParent.Fill(dset, "Client");
            daChild.Fill(dset, "MedicalImage");

            //fill in insert, update, delete command
            cmdBuilder= new SqlCommandBuilder(daChild);

            //adding the paret-child rel to the dataset
            dset.Relations.Add("ParentChild",
                dset.Tables["Client"].Columns["cid"],//primary key din tabelul nostru
                dset.Tables["MedicalImage"].Columns["cid"]); //foregin key din tabelul nostru

            //fill data into DataGridView
            //Method1
            //this.dataGridView1.DataSource = dset.Tables["Snowboard"];
            //this.dataGridView2.DataSource = this.dataGridView1.DataSource;
            //this.dataGridView2.DataMember = "ParentChild";

            //Method2: using data binding
            bsParent = new BindingSource();
            bsParent.DataSource = dset.Tables["Client"];
            bsChild = new BindingSource(bsParent, "ParentChild"); //chaining mechanism

            this.dataGridView1.DataSource = bsParent;
            this.dataGridView2.DataSource = bsChild;

            cmdBuilder.GetUpdateCommand();

        }

        string getConnectionString()
        {
            return "Data Source=DESKTOP-BVRD99U\\SQLEXPRESS; Initial Catalog=DentalCabinet;" + "Integrated Security=true;";
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            
            try
            {
                daChild.Update(dset, "MedicalImage");
                MessageBox.Show("Data uploaded successfully!");

            }

            catch(SqlException ex) {
                if (ex.Number == 2627) // validates the primary key; checks if it appears already or not
                {
                    MessageBox.Show("A snowboard with the same ID already exists");
                }
                else if (ex.Message.Contains("Cannot insert the value NULL into column"))
                {
                    MessageBox.Show("The ID field cannot be epmty. Please fill in the required field.");
                }
                else
                {
                    MessageBox.Show("An error occured while updating the data: " + ex.Message);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occured while updating the data: " + ex.Message);
            }
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {

        }
    }
}
