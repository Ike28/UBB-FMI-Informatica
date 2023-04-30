using System.Configuration;
using System.Data;
using System.Data.SqlClient;

namespace Laborator_2
{
    public partial class Form1 : Form
    {
        private SqlDataAdapter dataAdapter = new SqlDataAdapter();
        private DataSet dataSet = new DataSet();
        private string childTableName = ConfigurationManager.AppSettings["ChildTable"];
        private string parentTableName = ConfigurationManager.AppSettings["ParentTable"];
        private string columnNamesInsertParameters = ConfigurationManager.AppSettings["InsertParameterNames"];
        private List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["InputNames"].Split(','));
        private List<string> insertParameters = new List<string>(ConfigurationManager.AppSettings["InsertParameterNames"].Split(','));
        private List<string> columnInitiate = new List<string>(ConfigurationManager.AppSettings["ChildTextBoxContent"].Split(','));
        private SqlConnection connection = new SqlConnection(GetConnectionString());
        private int numberOfColumns = Convert.ToInt32(ConfigurationManager.AppSettings["ChildNumberOfColumns"]);
        private TextBox[] inputBoxes;
        private Label[] inputLabels;

        private static string GetConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["connectionString"].ConnectionString.ToString();
        }

        public Form1()
        {
            InitializeComponent();
            PopulatePanel();
            dataGridViewParent.SelectionChanged += new EventHandler(LoadChildren);
            dataGridViewSon.SelectionChanged += new EventHandler(LoadInformation);
            LoadParent();
        }

        private void LoadInformation(object sender, EventArgs e)
        {
            for (int i = 0; i < numberOfColumns; i++)
            {
                inputBoxes[i].Text = Convert.ToString(dataGridViewSon.CurrentRow.Cells[i + 1].Value);
            }
        }

        private void PopulatePanel()
        {
            inputBoxes = new TextBox[numberOfColumns];
            inputLabels = new Label[numberOfColumns];

            for (int i = 0; i < numberOfColumns; i++)
            {
                inputBoxes[i] = new TextBox();
                inputBoxes[i].Text = columnInitiate[i];
                inputLabels[i] = new Label();
                inputLabels[i].Text = columnNames[i];
            }

            for (int i = 0; i < numberOfColumns; i++)
            {
                panel1.Controls.Add(inputLabels[i]);
                panel1.Controls.Add(inputBoxes[i]);
            }
        }

        private void LoadParent()
        {
            string select = ConfigurationSettings.AppSettings["SelectParent"];
            dataAdapter.SelectCommand = new SqlCommand(select, connection);
            dataSet.Clear();
            dataAdapter.Fill(dataSet);
            dataGridViewParent.DataSource = dataSet.Tables[0];
        }

        private void LoadChildren(object sender, EventArgs e)
        {
            int parentId = (int)dataGridViewParent.CurrentRow.Cells[0].Value;
            string select = ConfigurationManager.AppSettings["SelectChild"];
            SqlCommand cmd = new SqlCommand(select, connection);
            cmd.Parameters.AddWithValue("@id", parentId);
            SqlDataAdapter childDataAdapter = new SqlDataAdapter(cmd);
            DataSet dataSet = new DataSet();

            childDataAdapter.Fill(dataSet);
            dataGridViewSon.DataSource = dataSet.Tables[0];
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            try
            {
                SqlCommand cmd = new SqlCommand("INSERT INTO " + childTableName + " ( " + ConfigurationManager.AppSettings["InputNames"] + " ) VALUES ( " + columnNamesInsertParameters + " )", connection);
                for (int i = 0; i < numberOfColumns; i++)
                {
                    cmd.Parameters.AddWithValue(insertParameters[i], inputBoxes[i].Text);
                }
                SqlDataAdapter childDataAdapter = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                connection.Open();
                childDataAdapter.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Successfully added!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                connection.Close();
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            try
            {
                string delete = ConfigurationManager.AppSettings["DeleteChild"];
                SqlCommand cmd = new SqlCommand(delete, connection);
                cmd.Parameters.AddWithValue("@id", dataGridViewSon.CurrentRow.Cells[0].Value);
                SqlDataAdapter childDataAdapter = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                connection.Open();
                cmd.ExecuteNonQuery();
                childDataAdapter.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Successfully deleted!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                connection.Close();
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                string update = ConfigurationManager.AppSettings["UpdateQuery"];
                SqlCommand cmd = new SqlCommand(update, connection);
                for (int i = 0; i < numberOfColumns; i++)
                {
                    cmd.Parameters.AddWithValue(insertParameters[i], inputBoxes[i].Text);
                }
                cmd.Parameters.AddWithValue("@id", dataGridViewSon.CurrentRow.Cells[0].Value);
                SqlDataAdapter childDataAdapter = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                connection.Open();
                childDataAdapter.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Updated!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                connection.Close();
            }
        }
    }
}