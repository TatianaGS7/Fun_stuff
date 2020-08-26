class HomeController < ApplicationController
  def index
  	@cmm = Comment.order("id DESC").limit(5)

    respond_to do |format|
      format.html # index.html.erb
      format.json { render json: @cmm }
    end
  end

end
