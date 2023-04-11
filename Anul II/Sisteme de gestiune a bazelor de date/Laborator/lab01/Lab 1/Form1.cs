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

namespace Lab_1
{
    public partial class Form1 : Form
    {
        string connectionString = @"Server=DESKTOP-UM07TFE;Initial Catalog=DiebmannImobiliare;Integrated Security=true;";
        DataSet ds = new DataSet();
        SqlDataAdapter adapter = new SqlDataAdapter();
        SqlDataAdapter sonAdapter = new SqlDataAdapter();

        public Form1()
        {
            InitializeComponent();
        }

        private void hideStuff()
        {
            label2.Visible = false;
            emailBox.Visible = false;
            emailLabel.Visible = false;
            phoneBox.Visible = false;
            phoneLabel.Visible = false;
            nameBox.Visible = false;
            nameLabel.Visible = false;
            idBox.Visible = false;
            idLabel.Visible = false;
            addButton.Visible = false;
            deleteButton.Visible = false;
            updateButton.Visible = false;
            //dataGridViewSon.Visible = false;
        }

        private void clearBoxes()
        {
            idBox.Clear();
            nameBox.Clear();
            phoneBox.Clear();
            emailBox.Clear();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using(SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Sedii", connection);
                    adapter.Fill(ds, "Sedii");
                    dataGridViewParent.DataSource = ds.Tables["Sedii"];
                    hideStuff();
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Form1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            try
            {
                using(SqlConnection connection = new SqlConnection(connectionString))
                {
                    adapter.SelectCommand.Connection = connection;
                    ds.Tables["Sedii"].Clear();
                    ds.Tables["Agenti"].Clear();
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Sedii;", connection);
                    adapter.Fill(ds, "Sedii");
                    sonAdapter.SelectCommand = new SqlCommand("SELECT * FROM Agenti", connection);
                    sonAdapter.Fill(ds, "Agenti");
                    dataGridViewParent.DataSource = ds.Tables["Sedii"];
                    dataGridViewSon.DataSource = ds.Tables["Agenti"];
                    hideStuff();
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void dataGridViewParent_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            try
            {
                using(SqlConnection connection = new SqlConnection(connectionString))
                {
                    dataGridViewSon.Visible = true;
                    adapter.SelectCommand.Connection = connection;
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Agenti", connection);
                    if (ds.Tables["Agenti"] != null)
                        ds.Tables["Agenti"].Clear();
                    adapter.Fill(ds, "Agenti");
                    dataGridViewSon.DataSource = ds.Tables["Agenti"];
                    label2.Visible = true;
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void dataGridViewSon_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            emailBox.Visible = true;
            emailLabel.Visible = true;
            phoneBox.Visible = true;
            phoneLabel.Visible = true;
            nameBox.Visible = true;
            nameLabel.Visible = true;
            idBox.Visible = true;
            idLabel.Visible = true;
            addButton.Visible = true;
            deleteButton.Visible = true;
            updateButton.Visible = true;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            using (SqlConnection cn = new SqlConnection(connectionString))
            {
                using (SqlCommand cmd = new SqlCommand("UPDATE Agenti SET nume=@nume, idSediuAsignat=@idSediu, telefon=@telefon, email=@email WHERE idAgent = @id", cn))
                {
                    if (cn.State == ConnectionState.Closed)
                        cn.Open();

                    DataGridViewRow row = dataGridViewSon.Rows[dataGridViewSon.CurrentRow.Index] as DataGridViewRow;
                    if (row != null
                        && (idBox.Text.Length != 0
                        || nameBox.Text.Length != 0
                        || phoneBox.Text.Length != 0
                        || emailBox.Text.Length != 0))
                    {
                        cmd.Parameters.AddWithValue("@id", row.Cells["idAgent"].Value);
                        if (idBox.Text.Length != 0)
                        {
                            cmd.Parameters.AddWithValue("@idSediu", idBox.Text);
                        }
                        else
                        {
                            cmd.Parameters.AddWithValue("@idSediu", row.Cells["idSediuAsignat"].Value);
                        }

                        if (nameBox.Text.Length != 0)
                        {
                            cmd.Parameters.AddWithValue("@nume", nameBox.Text);
                        }
                        else
                        {
                            cmd.Parameters.AddWithValue("@nume", row.Cells["nume"].Value);
                        }

                        if (phoneBox.Text.Length != 0)
                        {
                            cmd.Parameters.AddWithValue("@telefon", phoneBox.Text);
                        }
                        else
                        {
                            cmd.Parameters.AddWithValue("@telefon", row.Cells["telefon"].Value);
                        }

                        if (emailBox.Text.Length != 0)
                        {
                            cmd.Parameters.AddWithValue("@email", emailBox.Text);
                        }
                        else
                        {
                            cmd.Parameters.AddWithValue("@email", row.Cells["email"].Value);
                        }

                        cmd.ExecuteNonQuery();
                        clearBoxes();
                        buttonRefresh_Click(sender, e);
                        MessageBox.Show("Agent modificat.", "Succes!");
                    }
                    else
                    {
                        MessageBox.Show("Cel putin un camp trebuie modificat pentru actualizare", "Error");

                    }
                }
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            DataGridViewRow row = dataGridViewSon.Rows[dataGridViewSon.CurrentRow.Index] as DataGridViewRow;
            if (row != null)
            {
                if (MessageBox.Show("Doriti sa stergeti acest agent?", "Atentie", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                {
                    using (SqlConnection cn = new SqlConnection(connectionString))
                    {
                        if (cn.State == ConnectionState.Closed)
                            cn.Open();
                        using (SqlCommand cmd = new SqlCommand("DELETE FROM Agenti WHERE idAgent = @id", cn))
                        {
                            cmd.Parameters.AddWithValue("id", row.Cells["idAgent"].Value);
                            cmd.ExecuteNonQuery();
                            clearBoxes();
                            buttonRefresh_Click(sender, e);
                            MessageBox.Show("Agent sters.", "Succes!");
                        }
                    }
                }
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            using (SqlConnection cn = new SqlConnection(connectionString))
            {
                if (cn.State == ConnectionState.Closed)
                    cn.Open();
                using (SqlCommand cmd = new SqlCommand("INSERT INTO Agenti(idSediuAsignat,nume,telefon,email) VALUES(@idSediu,@nume,@telefon,@email)", cn))
                {
                    if (nameBox.Text.Length != 0
                        && phoneBox.Text.Length != 0
                        && emailBox.Text.Length != 0)
                    {
                        DataGridViewRow row = dataGridViewParent.Rows[dataGridViewParent.CurrentRow.Index] as DataGridViewRow;

                        cmd.Parameters.AddWithValue("@idSediu", row.Cells["idSediu"].Value);
                        cmd.Parameters.AddWithValue("@nume", nameBox.Text);
                        cmd.Parameters.AddWithValue("@telefon", phoneBox.Text);
                        cmd.Parameters.AddWithValue("@email", emailBox.Text);
                        cmd.ExecuteNonQuery();
                        clearBoxes();
                        buttonRefresh_Click(sender, e);
                        MessageBox.Show("Agent adaugat.", "Succes!");
                    }
                    else
                    {
                        MessageBox.Show("Adaugarea nu a putut avea loc:\n   * Toate campurile trebuiesc completate", "Eroare");
                    }
                }
            }
        }
    }
}
