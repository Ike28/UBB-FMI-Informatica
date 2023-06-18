using Microsoft.Data.SqlClient;
using System.Data;

namespace ExamenPractic
{
    public partial class Form1 : Form
    {
        string connectionString = @"Server=DESKTOP-GPMOU7L;Database=S32023;Integrated Security=true;TrustServerCertificate=true;";
        DataSet ds = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        BindingSource parentBS = new BindingSource();
        BindingSource childBS = new BindingSource();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    MessageBox.Show(connection.State.ToString());
                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Destinatii;", connection);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Sejururi;", connection);
                    parentAdapter.Fill(ds, "Destinatii");
                    childAdapter.Fill(ds, "Sejururi");
                    DataColumn parentColumn = ds.Tables["Destinatii"].Columns["cod_d"];
                    DataColumn childColumn = ds.Tables["Sejururi"].Columns["cod_d"];
                    DataRelation relation = new DataRelation("FK_Sejururi_Destinatii", parentColumn, childColumn);
                    ds.Relations.Add(relation);
                    parentBS.DataSource = ds.Tables["Destinatii"];
                    dataGridViewParent.DataSource = parentBS;
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "FK_Sejururi_Destinatii";
                    dataGridViewChild.DataSource = childBS;
                }
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(ex.Message);
            }
        }

        private void refreshTables()
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    ds.Clear();
                    parentAdapter.SelectCommand.Connection = connection;
                    childAdapter.SelectCommand.Connection = connection;
                    parentAdapter.Fill(ds, "Destinatii");
                    childAdapter.Fill(ds, "Sejururi");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }


        private void buttonAdd_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    SqlCommand addCommand = new SqlCommand("INSERT INTO Sejururi (nume_sejur, detalii_sejur, data_inceput, data_sfarsit, cod_d) " +
                        "VALUES (@nume_sejur, @detalii_sejur, @data_inceput, @data_sfarsit, @cod_d)", connection);
                    addCommand.Parameters.AddWithValue("@nume_sejur", dataGridViewChild.CurrentRow.Cells["nume_sejur"].Value);
                    addCommand.Parameters.AddWithValue("@detalii_sejur", dataGridViewChild.CurrentRow.Cells["detalii_sejur"].Value);
                    addCommand.Parameters.AddWithValue("@data_inceput", Convert.ToDateTime(dataGridViewChild.CurrentRow.Cells["data_inceput"].Value));
                    addCommand.Parameters.AddWithValue("@data_sfarsit", Convert.ToDateTime(dataGridViewChild.CurrentRow.Cells["data_sfarsit"].Value));
                    addCommand.Parameters.AddWithValue("@cod_d", Convert.ToInt32(dataGridViewChild.CurrentRow.Cells["cod_d"].Value));
                    childAdapter.UpdateCommand = addCommand;
                    addCommand.ExecuteNonQuery();
                    refreshTables();
                }
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(ex.Message);
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    SqlCommand updateCmd = new SqlCommand("UPDATE Sejururi SET nume_sejur=@nume_sejur, detalii_sejur=@detalii_sejur, data_inceput=@data_inceput, data_sfarsit=@data_sfarsit, cod_d=@cod_d " +
                        "WHERE cod_s=@cod_s", connection);
                    updateCmd.Parameters.AddWithValue("@nume_sejur", dataGridViewChild.CurrentRow.Cells["nume_sejur"].Value);
                    updateCmd.Parameters.AddWithValue("@detalii_sejur", dataGridViewChild.CurrentRow.Cells["detalii_sejur"].Value);
                    updateCmd.Parameters.AddWithValue("@data_inceput", Convert.ToDateTime(dataGridViewChild.CurrentRow.Cells["data_inceput"].Value));
                    updateCmd.Parameters.AddWithValue("@data_sfarsit", Convert.ToDateTime(dataGridViewChild.CurrentRow.Cells["data_sfarsit"].Value));
                    updateCmd.Parameters.AddWithValue("@cod_d", Convert.ToInt32(dataGridViewChild.CurrentRow.Cells["cod_d"].Value));
                    updateCmd.Parameters.AddWithValue("@cod_s", Convert.ToInt32(dataGridViewChild.CurrentRow.Cells["cod_s"].Value));
                    childAdapter.UpdateCommand = updateCmd;
                    updateCmd.ExecuteNonQuery();
                    refreshTables();
                }
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(ex.Message);
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    SqlCommand deleteCommand = new SqlCommand("DELETE FROM Sejururi WHERE cod_s=@cod_s", connection);
                    deleteCommand.Parameters.AddWithValue("@cod_s", Convert.ToInt32(dataGridViewChild.CurrentRow.Cells["cod_s"].Value));
                    childAdapter.UpdateCommand = deleteCommand;
                    deleteCommand.ExecuteNonQuery();
                    refreshTables();
                }
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(ex.Message);
            }
        }

        private void labelParent_Click(object sender, EventArgs e)
        {

        }
    }
}