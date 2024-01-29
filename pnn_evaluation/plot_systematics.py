import ROOT
import argparse
import re
def create_histogram(dataframe, column, title, color):
    """Create a histogram from a DataFrame column."""
    hist = dataframe.Filter(f'{column} > -9.9' ).Histo1D((title, title, 20, 0, 1), column)
    hist.SetLineColor(color)
    hist.SetLineWidth(2)
    return hist.GetPtr()  # Return the pointer to the histogram

def plot_nn_scores(input_file, nominal_name):
    # Enable RDataFrame multi-threading
    ROOT.ROOT.EnableImplicitMT()

    # Load the ROOT file
    df = ROOT.RDataFrame("ntuple", input_file)


    # Convert column names to strings and detect variations
    all_columns = [str(col) for col in df.GetColumnNames()]
    pattern = re.compile(rf"^{nominal_name}___(\w+)(Up|Down)$")
    variations = set(pattern.match(col).group(1) for col in all_columns if pattern.match(col))


    # Loop over each variation and create plots
    for variation in variations:
        up_name = f"{nominal_name}___{variation}Up"
        down_name = f"{nominal_name}___{variation}Down"

        # Create histograms
        hist_nominal = create_histogram(df, nominal_name, "Nominal", ROOT.kBlack)
        hist_up = create_histogram(df, up_name, "Up", ROOT.kRed)
        hist_down = create_histogram(df, down_name, "Down", ROOT.kBlue)
    
        hist_nominal.SetStats(0)
        hist_up.SetStats(0)
        hist_down.SetStats(0)

        # Create canvas
        canvas = ROOT.TCanvas("canvas", "", 800, 800)
        canvas.Divide(1, 2)
        
        # Upper pad for the score distributions
        pad1 = canvas.cd(1)
        pad1.SetPad(0, 0.3, 1, 1)
        pad1.SetBottomMargin(0.03)
        hist_nominal.Draw("HIST")
        hist_up.Draw("HISTSAME")
        hist_down.Draw("HISTSAME")

        # Add legend
        legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
        legend.AddEntry(hist_nominal, "Nominal", "l")
        legend.AddEntry(hist_up, "Up", "l")
        legend.AddEntry(hist_down, "Down", "l")
        legend.Draw()

        # Lower pad for the ratio plots
        pad2 = canvas.cd(2)
        pad2.SetPad(0, 0.05, 1, 0.3)
        pad2.SetTopMargin(0.03)
        pad2.SetBottomMargin(0.3)

        # Create and draw ratio histograms
        hist_ratio_up = hist_up.Clone("ratio_up")
        hist_ratio_up.Add(hist_nominal, -1)  # up - nominal
        hist_ratio_up.Divide(hist_nominal)   # (up - nominal) / nominal

        hist_ratio_down = hist_down.Clone("ratio_down")
        hist_ratio_down.Add(hist_nominal, -1)  # down - nominal
        hist_ratio_down.Divide(hist_nominal)   # (down - nominal) / nominal

        # Set Y-axis range from -1 to 1 for ratio plots
        hist_ratio_up.GetYaxis().SetRangeUser(-1, 1)
        hist_ratio_down.GetYaxis().SetRangeUser(-1, 1)

        # Draw ratio histograms
        hist_ratio_up.SetTitle("")
        hist_ratio_up.GetYaxis().SetTitle("Ratio (Up/Nominal)")
        hist_ratio_up.GetYaxis().SetNdivisions(505)
        hist_ratio_up.GetYaxis().SetTitleSize(0.1)
        hist_ratio_up.GetYaxis().SetTitleOffset(0.3)
        hist_ratio_up.GetYaxis().SetLabelSize(0.08)
        hist_ratio_up.GetXaxis().SetTitleSize(0.1)
        hist_ratio_up.GetXaxis().SetLabelSize(0.08)
        hist_ratio_up.Draw("HIST")
        hist_ratio_down.SetLineColor(ROOT.kBlue)
        hist_ratio_down.Draw("HISTSAME")
        line = ROOT.TLine(pad2.GetUxmin(), 0, pad2.GetUxmax(), 0)
        line.SetLineColor(ROOT.kBlack)
        line.SetLineStyle(2)
        line.Draw()

        # Save the canvas
        output_filename = f"{nominal_name}_{variation}.png"
        canvas.SaveAs(output_filename)
        print(f"Plot saved as {output_filename}")

def main():
    parser = argparse.ArgumentParser(description="Plot NN scores and their variations.")
    parser.add_argument("input_file", help="Path to the ROOT file")
    parser.add_argument("nominal_name", help="Nominal histogram name (e.g., 'pnn_100')")
    args = parser.parse_args()

    plot_nn_scores(args.input_file, args.nominal_name)

if __name__ == "__main__":
    main()